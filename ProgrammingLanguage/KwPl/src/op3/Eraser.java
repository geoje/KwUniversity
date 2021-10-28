package op3;

class Eraser implements Tool {

    @Override
    public void draw(int x, int y) {
        System.out.println(String.format("✐  지우개로 (%d, %d) 슥삭슥삭~", x, y));
    }

}
