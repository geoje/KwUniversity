package op1;

class Main {
	public static void main(String[] args) {
		// 강의가 개설된다.
		Lecture programmingLanguage = new Lecture();

		// 수간신청날에 강의를 신청한다.
		StudentAlice alice = new StudentAlice(programmingLanguage, "Alice");
		StudentBob bob = new StudentBob(programmingLanguage, "Bob");

		// 교수님께서 게시글을 올린다.
		programmingLanguage.addNewPost("코로나19에 따른 비대면 강의 공지", "앞으로 강의는 온라인 녹화 강의로 진행됩니다.");

		// 수간정정 기간에 새로운 학생이 들어온다.
		StudentMallory mallory = new StudentMallory(programmingLanguage, "Mallory");

		// 교수님께서 또 다른 게시글을 올린다.
		programmingLanguage.addNewPost("과제1 공지", "옵저버 패턴을 무엇인가?");

		// 수강 포기를 한다.
		bob.dropLecture();

		// 교수님께서 또 다른 게시글을 올린다.
		programmingLanguage.addNewPost("중간고사 공지", "중간고사는 과제 대체!");
	}
}
