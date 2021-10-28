package sp;

import java.util.ArrayList;
import java.util.Collections;

class StrategyPattern {
	public static void main(String[] args) {
		// 유저 생성
		User player = new User();

		// 무기 습득
		player.AddWeapon(new Pistol());
		player.AddWeapon(new Sword());
		player.AddWeapon(new Bow());

		// 필살기 2번 사용
		player.Pilsalgi();
		player.Pilsalgi();
	}
}


class User {
	ArrayList<Weapon> weapons;

	public User() {
		weapons = new ArrayList<>();
	}

	public void AddWeapon(Weapon w) {
		weapons.add(w);
	}

	public void Pilsalgi() {
		System.out.println("🏌️ 무기 뒤섞고!");
		Collections.shuffle(weapons);
		weapons.forEach(w -> w.attack());
		System.out.println();
	}
}


interface Weapon {
	public void attack();
}


class Sword implements Weapon {
	@Override
	public void attack() {
		System.out.println("🗡️ 검으로 슥삭!");
	}
}


class Bow implements Weapon {
	@Override
	public void attack() {
		System.out.println("🏹 활로 슉!");
	}
}


class Pistol implements Weapon {
	@Override
	public void attack() {
		System.out.println("🔫 총으로 빵!");
	}
}
