import java.io.*;
import java.sql.*;
// SQL ���� Ŭ������ java.sql .*�� ���ԵǾ� �ִ�.
public class BookList {
   Connection con;
// Ŭ���� booklist�� �����Ѵ�. java.sql�� Connection ��ü con�� �����Ѵ�.  	
   public BookList() {
     String Driver="";
     String 
url="jdbc:mysql://localhost:3306/madang?&serverTimezone=Asia/Seoul"; 
     String userid="madang";
     String pwd="madang";
// ���Ӻ����� �ʱ�ȭ�Ѵ�. url�� �ڹ� ����̹� �̸�, ȣ��Ʈ��(localhost), ��Ʈ��ȣ�� �Է��Ѵ�
// userid�� ������(madang), pwd�� ������� ��й�ȣ(madang)�� �Է��Ѵ�.    
     try { /* ����̹��� ã�� ���� */
       Class.forName("com.mysql.cj.jdbc.Driver");   
       System.out.println("����̹� �ε� ����");
     } catch(ClassNotFoundException e) {
         e.printStackTrace();
      }
// Class.forName()���� ����̹��� �ε��Ѵ�. ����̹� �̸��� Class.forName�� �Է��Ѵ�.      
     try { /* �����ͺ��̽��� �����ϴ� ���� */
       System.out.println("�����ͺ��̽� ���� �غ�...");	
       con=DriverManager.getConnection(url, userid, pwd);
       System.out.println("�����ͺ��̽� ���� ����");
     } catch(SQLException e) {
         e.printStackTrace();
       }
   }
// ���� ��ü con�� DriverManager.getConnection �Լ��� �����Ѵ�. 
// ������ �����ϸ� "�����ͺ��̽� ���� ����"�� ����ϵ��� �Ѵ�.  
// ���ڿ� query�� ������ SQL ���� �Է��Ѵ�.
   private void sqlRun() {
  	  String query="SELECT * FROM Book"; /* SQL �� */
  	  try { /* �����ͺ��̽��� ���� ����� �������� ���� */
  	  	 Statement stmt=con.createStatement();
  	  	 ResultSet rs=stmt.executeQuery(query);
  	  	 System.out.println(" BOOK NO \tBOOK NAME \t\tPUBLISHER \tPRICE ");
  	  	 while(rs.next()) {
  	  	 	System.out.print("\t"+rs.getInt(1));
  	  	 	System.out.print("\t"+rs.getString(2));
  	  	 	System.out.print("\t\t"+rs.getString(3));
  	  	 	System.out.println("\t"+rs.getInt(4));
  	  	 }
  	  	 
  	  	 con.close();
  	  } catch(SQLException e) {
  	  	   e.printStackTrace();
  	    }
   }
  	  
  	public static void main(String args[]) {
  	   BookList so=new BookList();
  	   so.sqlRun();
  	}
}