package op3;

class Canvas implements Observer {
    Tool curTool;

    public Canvas() {
        curTool = new Pencil();
    }

    @Override
    public void update(MouseEvent mouseevent) {
        curTool.draw(mouseevent.x, mouseevent.y);
    }

    @Override
    public void update(KeyboardEvent keyevent) {
        if (keyevent.key == 'p') {
            curTool = new Pencil();
            System.out.println("✍️  도구 변경 - 펜");
        } else if (keyevent.key == 'e') {
            curTool = new Eraser();
            System.out.println("✐  도구 변경 - 지우개");
        }
    }
}
