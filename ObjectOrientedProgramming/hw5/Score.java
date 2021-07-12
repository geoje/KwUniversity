package application;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Score {
	private StringProperty name;
	private IntegerProperty korean, math, english;
	
	public Score(String name, int korean, int math, int english) {
		this.name = new SimpleStringProperty(name);
		this.korean = new SimpleIntegerProperty(korean);
		this.math = new SimpleIntegerProperty(math);
		this.english = new SimpleIntegerProperty(english);
	}
	
	public StringProperty NameProperty() {
		return name;
	}
	public IntegerProperty KoreanProperty() {
		return korean;
	}
	public IntegerProperty MathProperty() {
		return math;
	}
	public IntegerProperty EnglishProperty() {
		return english;
	}
}
