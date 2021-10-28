package op3;

public class CloseButton implements Observer {

    @Override
    public void update(MouseEvent mouseevent) {
        if (mouseevent.x >= 0 && mouseevent.y >= 0 && mouseevent.x <= 10 && mouseevent.y <= 10)
            System.out.println("🚪  [종료 버튼] 버튼 위치 (0,0) - (10,10) 사이가 눌려져서 프로그램을 종료합니다.");
    }

    @Override
    public void update(KeyboardEvent keyevent) {
        if (Character.toUpperCase(keyevent.key) == 'Q')
            System.out.println("🚪  [종료 버튼] Q 입력이 감지 되어 프로그램을 종료합니다.");
    }

}
