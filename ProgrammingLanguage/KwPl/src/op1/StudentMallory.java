package op1;

class StudentMallory extends Student {
    public StudentMallory(Subject lecture, String name) {
        super(lecture, name);
    }

    @Override
    public void update(Post post) {
        readPost();
    }

    @Override
    public void readPost() {
        System.out.println(String.format("[%s] 귀찮아서 안볼거에요.", name));
    }
}
