import java.io.*;
import java.sql.*;

public class V8c {
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
			ResultSet rs = stmt.executeQuery("SELECT Ssn,Salary FROM EMPLOYEE");
			PreparedStatement pstmt = conn.prepareStatement( "UPDATE EMPLOYEE SET Salary = Salary + 100 WHERE Ssn = ?");
			while (rs.next()) {
				String ssn = rs.getString("Ssn");
				pstmt.setString(1, ssn);
				pstmt.executeUpdate();
			}
			System.out.println("Salary increased by 100");
			rs = stmt.executeQuery("SELECT Salary FROM EMPLOYEE");
			while (rs.next()) {
				System.out.println(rs.getDouble("Salary"));
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
