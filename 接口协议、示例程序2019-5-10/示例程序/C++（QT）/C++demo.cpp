

//----------------��ȡ��Ȩ����------------------------
void NetWork::postToken(const QString urlStr)
{
	//��Ȩurl http://111.47.23.188:9876/platform/auth
	QUrl url(urlStr);

	QVariantMap login;
	//�û���  ����
	login.insert("password","xxxxx");
	login.insert("login","xxxxx");


	//���л�Ϊjson��ʽ
	QJson::serializer;
	bool ok;

	QVariantList postTest;


	serializer.setIndentMode(QJson::IndentCompact);
	QByteArray dataArray = serializer.serialize(login, &ok);

	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setUrl(url);

	//����post����
	QNetworkReply *reply = manager->post(request, dataArray.data());

	connect(reply, SIGNAL(finished()), this, SLOT(getTokenFinished()),Qt::UniqueConnection);

}

//��ȡ��Ӧ�¼�
void NetWork::getTokenFinished()
{
	QNetworkReply* reply = (QNetworkReply*)sender();

	//��ȡ��Ӧ��Ϣ
	QByteArray bytes = reply->readAll();

	reply->deleteLater();

	if (bytes.isEmpty())
	{
		qDebug() << "��ȡtokenʧ��";

		return;
	}


	QString jsonData = tc->toUnicode(bytes);

	//��ȡTokenֵ������
	//�����ص�json��ʽ�����л�Ϊqbytearray
	QVariantMap vm = Json::parserJson(jsonData);

	QString tokenTmp = vm.value("accessToken").toString();

	emit slTokenString(tokenTmp);
	token = tokenTmp;
}



//----------------�ϴ�����������------------------------
void NetWork::sendTracktoTHY( const QString urlStr, FlyStatusData trackData )
{
	QString baseUrl = urlStr + "/dc/single-aircrafts/antiuav";
	QUrl url(baseUrl);

	//ƴ�Ӻ�������
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

	//���������л�Ϊjson��ʽ
	QJson::Serializer serializer;
	bool ok;

	serializer.setIndentMode(QJson::IndentCompact);

	QByteArray CompeteDatas = serializer.serialize(jsonTrackDataGDY, &ok);

	//���heard ,��֤��Ϣ
	QString azContents = rawHeader + token;
	QNetworkRequest request;
	QSslConfiguration config;

	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1);
	request.setSslConfiguration(config);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setRawHeader("Authorization", azContents.toAscii());
	request.setUrl(url);

	//����Post����
	QNetworkReply *reply = manager->post(request, CompeteDatas);

	connect(reply, SIGNAL(finished()), this, SLOT(sendTrackFinished()),Qt::UniqueConnection);
}

//��Ӧ�¼�
void NetWork::sendTrackFinished()
{
	QNetworkReply* reply = (QNetworkReply*)sender();
	reply->deleteLater();


	//��ȡ��Ӧ��Ϣ
	QByteArray bytes = reply->readAll();

	QString status = tc->toUnicode(bytes);

	emit slPostStatisString(status);

}


