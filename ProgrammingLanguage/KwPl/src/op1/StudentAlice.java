package op1;

class StudentAlice extends Student {
    private String title, content;

    public StudentAlice(Subject lecture, String name) {
        super(lecture, name);
    }

    @Override
    public void update(Post post) {
        title = post.title;
        content = post.content;
        readPost();
    }

    @Override
    public void readPost() {
        System.out.println(String.format("[%s] 새로운 게시글 (제목: %s... / 내용: %s...) 읽었어요!", name,
                title.split(" ")[0], content.split(" ")[0]));
    }
}
