# 읽고 있는 책
하이브리드 앱을 구현하는 기술 - 구보타 미츠노리, 한빛미디어, 2015

# 코도바를 이용한 앱 개발 흐름 (4장)
## 개발환경 구축

### node.js 설치
- npm을 이용하여 편리하게 설치할 수 있음. 따라서, node.js 설치가 필요함.
- node.js 설치 : http://nodejs.org
- node.js 버전 확인 ``` $ node -v ```
- npm 버전 확인 ``` $ npm -v ```

### cordova 설치
``` $ npm install cordova -g ```
- ** cordova 버전 확인 ``` $ cordova -v ``` **
- Android 나 필요한 환경변수들 설정해야 함.

### 프로젝트 생성
**``` $ cordova create hello com.example.hello HelloWorld -d ```**

Parameter|설명
----|----
create|프로젝트 생성 명령
hello|생성할 디렉토리. PWD 아래 생성됨
com.example.hello|앱 식별자
HelloWorld|프로젝트 이름
-d|명령 실행 과정을 표시하라는 옵션

### 플랫폼 관리 명령
명령|기능
----|----
``` $ cordova platform add ios```|플랫폼 추가 명령. iso, android, browser 등 가능
``` $ cordova platform ls```|가용한 플랫폼 및 추가된 플랫폼 목록 확인
``` $ cordova platform remove ios```|플랫폼 제거

### 프로젝트 디렉토리 구조
(cordova 버전에 따라 조금 다름)
```
hello /
    config.xml --> 프로젝트 설정 파일 저장
    hooks      --> 사용자 스크립트 저장
    platforms  --> 각 프랫폼 고유의 프로젝트 파일
    merges     --> 각 플랫폼의 리소스.
    plugins    --> 플러그인
    www        --> HTML5 리소스와 앱 설정 파일
```
