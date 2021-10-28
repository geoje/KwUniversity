package op3;

class Pencil implements Tool {

    @Override
    public void draw(int x, int y) {
        System.out.println(String.format("✍️  연필로 (%d, %d) 끄적끄적!", x, y));
    }
}
