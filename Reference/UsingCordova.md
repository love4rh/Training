# 책에 대하여
- 제목: 하이브리드 앱을 구현하는 기술
- 저자: 구보타 미츠노리, 아시알 주식회사
- 역자: 김성재
- 한빛미디어, 2015

# 코도바를 이용한 앱 개발 흐름 (4장)
## 개발환경 구축

### node.js 설치
- npm을 이용하여 편리하게 설치할 수 있음. 따라서, node.js 설치가 필요함.
- node.js 설치 : http://nodejs.org
- node.js 버전 확인 `$ node -v`
- npm 버전 확인 ``$ npm -v`

### cordova 설치
``` $ npm install cordova -g ```
- npm ERR! 와 같은 오류가 나오면 sudo 권한으로 실행할 것
- **cordova 버전 확인 `$ cordova -v``**
- Android 나 필요한 환경변수들 설정해야 함.
- 특정 버전을 설치하고 싶은 경우 `$ npm install cordova@3.0.6 -g `

### 프로젝트 생성
**` $ cordova create hello com.example.hello HelloWorld -d `**

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
`$ cordova platform add ios`|플랫폼 추가 명령. iso, android, browser 등 가능
`$ cordova platform ls`|가용한 플랫폼 및 추가된 플랫폼 목록 확인
`$ cordova platform remove ios`|플랫폼 제거

프로젝트 디렉토리에서 실행해야 함.

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

### 에뮬레이터 이용
```
$ cordova emulate android -d
```
#### iOS 시뮬레이터 이용
iOS 시뮬레이터를 커멘드라인에서 다루기 위한 도구인 ios-sim을 이용
ios-sim은 `Homebrew`를 이용하여 설치하며 OS X용 패키지 관리 도구임. (http://brew.sh)
Homebrew가 설치되지 않았다면,
```
$ ruby -e "$(curl -fsSL https://raw.github.com/mxcl/homebrew/go/install)"
```
Homebrew를 이용하여 iso-sim 설치 `$ brew install ios-sim`
ios-sim 설치가 끝나다면 다음 명령으로 iOS 시뮬레이터 실행
```
$ cordova emulate ios -d
```

### 실제 디바이스 프로젝트 실행하기
```
$ cordova run android
$ cordova run ios
```
-d 옵션을 붙여 명령 실행 과정을 확인할 수 있음.

### 업데이트 관리
```
$ npm update cordova -g
```

## Cordova를 이용한 앱 개발
- index.html : Cordova가 제일 처음 읽는 파일

### deviceready 이벤트
- 네이티브 기능을 이용하려면 네이티브와 HTML5를 연결하는 브릿지가 초기화 되어야 함.
- 이 초기화 처리가 끝나면 발생하는 이벤트가 deviceready임.
- 따라서, deviceready 이벤트 확인 후 처리해야 함.

###### HTML 파일을 읽을 때 발생하는 이벤트 및 순서
순서|이벤트|발생 타이밍
:----:|----|----
1|DOMContentLoaded|HTML의 모든 DOM 요소를 읽었을 때
2|load|해당 페이지의 렌더링에 필요한 리소스를 모두 읽었을 때
3|deviceready|자바스크립트로 네이티브 기능에 접근 준비가 되었을 때

## 앱 설정
프로젝트 루트에 있는 config.xml 파일 이용.

### config.xml 구조
```xml
<widget>
  <name></name> <!-- 프로젝트 명 -->
  <preference /> <!-- 속성으로 name, value 지정 -->
  <feature> <!-- 사용할 native 기능 정의. Plugins 설정 -->
    <param />
  </feature>
  <access /> <!-- 앱에서 허용할 도메인 -->
  <content src="index.html" /> <!-- 처음 읽을 HTML 경로 지정. 기본값: index.html -->
</widget>
```

###### preference 요소
```xml
<preference name="속성명" value="속성 값" />
