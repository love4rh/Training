# 읽고 있는 책
하이브리드 앱을 구현하는 기술 - 구보타 미츠노리, 한빛미디어, 2015

# 코도바를 이용한 앱 개발 흐름 (4장)
## 개발환경 구축
- npm을 이용하여 편리하게 설치할 수 있음. 따라서, node.js 설치가 필요함.
node.js 설치 : http://nodejs.org
node.js 버전 확인 ``` $ node -v ```
npm 버전 확인 ``` $ npm -v ```

- cordova 설치 ``` $ npm install cordova -g ```

- cordova 버전 확인 ``` $ cordova -v ```

- Android 나 필요한 환경변수들 설정해야 함.

## 프로젝트 생성
``` $ cordova create hello com.example.hello HelloWorld -d ```

Parameter|설명
----|----
create|프로젝트 생성 명령
hello|생성할 디렉토리. PWD 아래 생성됨
com.example.hello|앱 식별자
HelloWorld|프로젝트 이름
-d|명령 실행 과정을 표시하라는 옵션
