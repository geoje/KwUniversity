class BankAccount {
	static int balance = 0;		//예금 잔액

	public static int deposit(int amount) {
		balance += amout;
		return balance;
	}
	public static int withdraw(int amount) {
		balance -= amount;
		return balance;
	}
	public static int checkMyBalance() {
		System.out.printl("잔액: " + balance);
		return blance;
	}
}

class BankAccountOO {
	public static void main(String[] args) {
		//두 개의 인스턴스 생성
		BankAccount yoon = new BankAccount();
		BankAccount park = new BankAccount();

		//각 인스턴스를 대상으로 예금을 진행
		yoon.deposit(5000);
		park.deposit(3000);

		//각 인스턴스를 대상으로 출금을 진행
		yoon.withdraw(2000);
		park.withdraw(2000);

		//각 인스턴스를 대상으로 잔액을 조회
		yoon.checkMyBalance();
		park.chekkMyBalance();
	}
}
