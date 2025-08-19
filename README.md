# Project PineapplePizza
언리얼 엔진을 활용한 싱글플레이 게임 프로젝트  
4개의 스테이지(플랫포머, FPS, 장애물 피하기, 격투)로 구성된 팀 프로젝트입니다.  

## Screenshots
<table>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/5e73e8a0-7ed1-4765-9157-b84250b4aa07" width = "400"/></td>
    <td><img src="https://github.com/user-attachments/assets/5e97654b-6a66-4a78-9aad-16ecaf5e477d" width="400"/></td>
  </tr>
</table>
<table>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/4e303da2-2b8d-49a4-a264-6e90755f0dea" width = "400"/></td>
    <td><img src="https://github.com/user-attachments/assets/96228dce-bc70-4d29-938f-6b80c40258f2" width="400"/></td>
  </tr>
</table>

###
[소스코드](https://github.com/Kim-Ye-Sung/Portfolio/tree/main/PineapplePizza_Source)

## Features
- **Stage 1:** 플랫포머 형식의 점프 & 이동
- **Stage 2:** 1인칭 슈팅(FPS) 전투
- **Stage 3:** 장애물 피하기 (제가 전담 제작한 스테이지)
- **Stage 4:** 멀티플레이 격투

## Tech Stack
- Unreal Engine 5.4.4  
- C++ / Blueprints

## My Role
- Stage 3(장애물 피하기) 전담 개발  
  - 장애물 스폰 시스템 구현  
  - 이동 기계 및 충돌 판정 처리  
  - 타인의 캐릭터 코드 분석 및 수정  
- 멀티플레이 캐릭터 `AGosooPlayer` 및 상태 관리 시스템 제작  
- 추격/순찰 AI 미니언(`AUS_Minion`) C++ 구현  

## How to Run
1. Clone this repository
2. Open `Project_Gosoo.uproject` with Unreal Engine 5
3. Press **Play** to start the game
