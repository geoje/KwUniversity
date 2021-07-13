class BankAccountPO {
	static int balance = 0;

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

class PassingRef {
	public static void main(String args[]) {
		BankAcount ref1 = new BankAccount();
		BankAccont ref2 = ref1;	//ref1이 참조하는 대상을 r

		ref1.deposit(3000);
		ref2.deposit(2000);
		ref1.withdraw(400);
		ref2.withdraw(300);
		ref1.checkMyBalance();
		ref2.checkMyBalance();
	}
}
