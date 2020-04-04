#include "Session.h"
#include "MainApp.h"
#include "MainWindow.h"
SessionTCP::SessionTCP(const StreamSocket& s) : TCPServerConnection(s)
{
}

void SessionTCP::run()
{
	StreamSocket& ss = socket();
	SocketAddress peer = ss.address();
	IPAddress address =  peer.host();
	try {
		int n;
		int bytes = ss.receiveBytes(&n, sizeof(int));
		char buffer[1024];

		if (n == SessionTCP::ID_MESSAGE)
		{

			while (bytes > 0)
			{
				int size;
				int bytes = ss.receiveBytes(&size, sizeof(int));

				int n = ss.receiveBytes(buffer, sizeof(buffer));
				buffer[size] = '\0';
				MainApp& reference = wxGetApp();
				reference.frame->OnReceive(std::string(buffer, n), address.toString());
			}



		}

		else if (n == SessionTCP::ID_FILE)
		{
			SocketStream ostr(ss);
			Poco::FileOutputStream istr("test1", std::ios::binary);
			Poco::StreamCopier::copyStream(ostr, istr);
		}

		else if (n == SessionTCP::ID_STREAM)
		{
			using namespace cv;
			using namespace std;
			using namespace Poco::Net;

			Mat img;

			while (true)
			{
				Mat  img = Mat::zeros(480, 640, CV_8UC3); //return Mat in specific row and column count
				int  imgSize = img.total() * img.elemSize();
				
				uchar *sockData = new uchar[imgSize];


				for (int i = 0; i < imgSize; i += bytes) {
					if ((bytes = ss.receiveBytes( sockData + i, imgSize - i, 0)) == -1) {
						break;
					}
				}

				int ptr = 0;
				for (int i = 0; i < img.rows; i++) { //for each column and row assign given uchar
					for (int j = 0; j < img.cols; j++) {
						img.at<cv::Vec3b>(i, j) = cv::Vec3b(sockData[ptr + 0], sockData[ptr + 1], sockData[ptr + 2]);
						ptr = ptr + 3;
					}
				}

				imshow("WebCam", img);
				delete sockData;

				char key = waitKey(30);

				if (key == 27) //ESCAPE
					break;
			}


		}
	}

		
	

	catch (Poco::Exception & exc)
	{
		//
	}
}