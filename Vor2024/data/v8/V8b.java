import java.io.*;
import java.sql.*;

public class V8b {
	public static void main(String args[]) throws SQLException {
		String url = "jdbc:sqlite:/home/ragnar/school/data/v8/company.db";
		Connection conn = null;

		try {
			conn = DriverManager.getConnection(url);
			System.out.println("Connection established successfully");
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			Statement stmt = conn.createStatement();
			stmt.executeUpdate("UPDATE EMPLOYEE SET Salary = Salary * 1.05");
			ResultSet rs = stmt.executeQuery("SELECT Salary FROM EMPLOYEE");
			System.out.println("Laun hækkuð um 5%");
			while (rs.next()) {
				double n = rs.getDouble("Salary");
				System.out.println(n);
			}
			rs.close();

			try {
				if (conn != null) {
					conn.close();
				}
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
		}

	}
}
