import java.io.*;
import java.sql.*;

public class V8a {
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
			ResultSet rs = stmt.executeQuery("SELECT SUM(Salary) AS Sum FROM EMPLOYEE");
			while (rs.next()) {
				System.out.println("Heildarlaun: " + rs.getDouble("Sum"));
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
