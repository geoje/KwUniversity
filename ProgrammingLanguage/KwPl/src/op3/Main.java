package op3;

class Main {
    public static void main(String[] args) {
        // 키보드(COX) 마우스(Logitech) 생성
        Keyboard ck87 = new Keyboard();
        Mouse g102 = new Mouse();

        // 그림판 실행 - 캔버스, 종료 버튼 생성
        Canvas canvas = new Canvas();
        CloseButton btnClose = new CloseButton();

        // 이벤트가 생기면 알려달라고 키보드와 마우스에 켄버스와 종료버튼 등록
        ck87.registerObserver(canvas);
        ck87.registerObserver(btnClose);
        g102.registerObserver(canvas);
        g102.registerObserver(btnClose);

        // 여러가지 키보드, 마우스 입력
        g102.performMouseClick(10, 20);
        g102.performMouseClick(40, 30);
        ck87.performKeyDown('e');
        g102.performMouseClick(40, 30);

        // 프로그램 종료
        ck87.performKeyDown('q');
    }
}
