package application;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.XYChart;
import javafx.scene.chart.XYChart.Series;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

public class RootController implements Initializable {
	@FXML
	private TableView<Score> tvScore;
	@FXML
	private TableColumn<Score, String> tcName;
	@FXML
	private TableColumn<Score, Integer> tcKorean, tcMath, tcEnglish;
	@FXML
	private Button btnAdd, btnGraph;

	private Stage primaryStage;

	@Override
	public void initialize(URL location, ResourceBundle resoures) {
		tcName.setCellValueFactory(cellData -> cellData.getValue().NameProperty());
		tcKorean.setCellValueFactory(cellData -> cellData.getValue().KoreanProperty().asObject());
		tcMath.setCellValueFactory(cellData -> cellData.getValue().MathProperty().asObject());
		tcEnglish.setCellValueFactory(cellData -> cellData.getValue().EnglishProperty().asObject());
		
		tcName.setStyle("-fx-alignment: CENTER");
		tcKorean.setStyle("-fx-alignment: CENTER");
		tcMath.setStyle("-fx-alignment: CENTER");
		tcEnglish.setStyle("-fx-alignment: CENTER");
	}

	public void setPrimaryStage(Stage primaryStage) {
		this.primaryStage = primaryStage;
	}

	public void btnAddOnAction(ActionEvent e) throws Exception {
		Stage dialog = new Stage(StageStyle.UTILITY);
		dialog.initModality(Modality.WINDOW_MODAL);
		dialog.initOwner(primaryStage);
		dialog.setTitle("추가");

		Parent parent = FXMLLoader.load(getClass().getResource("AddDialog.fxml"));
		TextField txtName = (TextField) parent.lookup("#txtName");
		TextField txtKorean = (TextField) parent.lookup("#txtKorean");
		TextField txtMath = (TextField) parent.lookup("#txtMath");
		TextField txtEnglish = (TextField) parent.lookup("#txtEnglish");

		((Button) parent.lookup("#btnSave")).setOnAction(event -> {
			Score data = new Score(txtName.getText(), Integer.parseInt(txtKorean.getText()),
					Integer.parseInt(txtMath.getText()), Integer.parseInt(txtEnglish.getText()));
			if (tvScore.getItems() == null)
				tvScore.setItems(FXCollections.observableArrayList(data));
			else
				tvScore.getItems().add(data);
			dialog.close();
		});
		((Button) parent.lookup("#btnCancel")).setOnAction(event -> dialog.close());

		Scene scene = new Scene(parent);
		dialog.setScene(scene);
		dialog.setResizable(false);
		dialog.show();
	}

	public void btnChartOnAction(ActionEvent e) throws Exception {
		if (tvScore.getItems() == null)
			return;

		Stage dialog = new Stage(StageStyle.UTILITY);
		dialog.initModality(Modality.WINDOW_MODAL);
		dialog.initOwner(primaryStage);
		dialog.setTitle("막대 그래프");

		Parent parent = FXMLLoader.load(getClass().getResource("ChartDialog.fxml"));
		@SuppressWarnings("unchecked")
		BarChart<String, Integer> bcScore = (BarChart<String, Integer>) parent.lookup("#bcScore");

		ObservableList<XYChart.Data<String, Integer>> listKorean = FXCollections.observableArrayList();
		ObservableList<XYChart.Data<String, Integer>> listMath = FXCollections.observableArrayList();
		ObservableList<XYChart.Data<String, Integer>> listEnglish = FXCollections.observableArrayList();
		for (int i = 0; i < tvScore.getItems().size(); i++) {
			Score score = tvScore.getItems().get(i);
			String name = score.NameProperty().get();
			listKorean.add(new XYChart.Data<>(name, score.KoreanProperty().get()));
			listMath.add(new XYChart.Data<>(name, score.MathProperty().get()));
			listEnglish.add(new XYChart.Data<>(name, score.EnglishProperty().get()));
		}
		XYChart.Series<String, Integer> seriesKorean = new Series<>("국어", listKorean);
		XYChart.Series<String, Integer> seriesMath = new Series<>("수학", listMath);
		XYChart.Series<String, Integer> seriesEnglish = new Series<>("영어", listEnglish);

		bcScore.getData().add(seriesKorean);
		bcScore.getData().add(seriesMath);
		bcScore.getData().add(seriesEnglish);

		((Button) parent.lookup("#btnClose")).setOnAction(event -> dialog.close());

		Scene scene = new Scene(parent);
		dialog.setScene(scene);
		dialog.setResizable(false);
		dialog.show();
	}
}
