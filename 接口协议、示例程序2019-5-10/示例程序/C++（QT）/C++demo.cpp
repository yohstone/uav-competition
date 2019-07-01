

//----------------获取鉴权部分------------------------
void NetWork::postToken(const QString urlStr)
{
	//鉴权url http://111.47.23.188:9876/platform/auth
	QUrl url(urlStr);

	QVariantMap login;
	//用户名  密码
	login.insert("password","xxxxx");
	login.insert("login","xxxxx");


	//序列化为json格式
	QJson::serializer;
	bool ok;

	QVariantList postTest;


	serializer.setIndentMode(QJson::IndentCompact);
	QByteArray dataArray = serializer.serialize(login, &ok);

	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setUrl(url);

	//发送post请求
	QNetworkReply *reply = manager->post(request, dataArray.data());

	connect(reply, SIGNAL(finished()), this, SLOT(getTokenFinished()),Qt::UniqueConnection);

}

//获取响应事件
void NetWork::getTokenFinished()
{
	QNetworkReply* reply = (QNetworkReply*)sender();

	//获取响应信息
	QByteArray bytes = reply->readAll();

	reply->deleteLater();

	if (bytes.isEmpty())
	{
		qDebug() << "获取token失败";

		return;
	}


	QString jsonData = tc->toUnicode(bytes);

	//获取Token值并保存
	//将返回的json格式反序列化为qbytearray
	QVariantMap vm = Json::parserJson(jsonData);

	QString tokenTmp = vm.value("accessToken").toString();

	emit slTokenString(tokenTmp);
	token = tokenTmp;
}



//----------------上传单个点数据------------------------
void NetWork::sendTracktoTHY( const QString urlStr, FlyStatusData trackData )
{
	QString baseUrl = urlStr + "/dc/single-aircrafts/antiuav";
	QUrl url(baseUrl);

	//拼接航迹数据
	QVariantMap jsonTrackDataGDY;
	jsonTrackDataGDY.insert("ID", trackData.ID);
	jsonTrackDataGDY.insert("Longitude", trackData.Longitude);
	jsonTrackDataGDY.insert("Latitude", trackData.Latitude);
	jsonTrackDataGDY.insert("Altitude", trackData.Altitude);
	jsonTrackDataGDY.insert("Speed", trackData.Speed);
	jsonTrackDataGDY.insert("Direction", trackData.Direction);
	jsonTrackDataGDY.insert("Pitch", trackData.Pitch);
	jsonTrackDataGDY.insert("Roll", trackData.Roll);
	jsonTrackDataGDY.insert("Device", trackData.Device);
	jsonTrackDataGDY.insert("Timestamp", trackData.Timestamp);

	//将数据序列化为json格式
	QJson::Serializer serializer;
	bool ok;

	serializer.setIndentMode(QJson::IndentCompact);

	QByteArray CompeteDatas = serializer.serialize(jsonTrackDataGDY, &ok);

	//添加heard ,验证信息
	QString azContents = rawHeader + token;
	QNetworkRequest request;
	QSslConfiguration config;

	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1);
	request.setSslConfiguration(config);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setRawHeader("Authorization", azContents.toAscii());
	request.setUrl(url);

	//发送Post请求
	QNetworkReply *reply = manager->post(request, CompeteDatas);

	connect(reply, SIGNAL(finished()), this, SLOT(sendTrackFinished()),Qt::UniqueConnection);
}

//响应事件
void NetWork::sendTrackFinished()
{
	QNetworkReply* reply = (QNetworkReply*)sender();
	reply->deleteLater();


	//获取响应信息
	QByteArray bytes = reply->readAll();

	QString status = tc->toUnicode(bytes);

	emit slPostStatisString(status);

}


