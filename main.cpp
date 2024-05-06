#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    // 노트북 내장 웹캠을 사용하여 비디오 캡처 초기화 (카메라 ID: 0)
    VideoCapture cap(0);

    // 카메라 해상도 조절
    cap.set(CAP_PROP_FRAME_WIDTH, 640); 
    cap.set(CAP_PROP_FRAME_HEIGHT, 480); 

    // 카메라를 열 수 없는 경우 종료
    if (!cap.isOpened()) {
        cout << "카메라를 열 수 없습니다." << endl;
        return -1;
    }

    // 얼굴 검출기 로드
    CascadeClassifier face_cascade;
    if (!face_cascade.load("C:\\Users\\fpemq\\Downloads\\haarcascade_frontalface_default.xml")) {
        cout << "얼굴 검출기 파일을 로드할 수 없습니다." << endl;
        return -1;
    }

    // 캡처된 이미지 저장을 위한 Mat 변수
    Mat img;

    while (true) {
        // 비디오 스트림에서 프레임을 캡처
        cap >> img;

        // 이미지 좌우 반전
        flip(img, img, 1);

        // 그레이스케일 변환
        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        // 얼굴 검출
        vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.3, 5); // 매개변수 조정

        // 감지된 얼굴 주위에 사각형 그리기
        for (const Rect& face : faces) {
            rectangle(img, face, Scalar(0, 255, 0), 2);
        }

        // 캡처한 이미지를 화면에 표시
        imshow("Camera Feed", img);

        // ESC 키를 누르면 루프를 종료하고 프로그램을 종료
        if (waitKey(1) == 27) {
            break;
        }
    }

    // 카메라 리소스 해제 및 모든 창 닫기
    cap.release();
    destroyAllWindows();

    return 0;
}
