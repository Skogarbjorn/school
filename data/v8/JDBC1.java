
import java.io.*;
import java.sql.*;
import java.util.Scanner;

class JDBC1
{
	public static void main( String[] args )
		throws Exception
	{
		Connection conn;
		try
		{
			Class.forName("org.postgresql.Driver");
			java.util.Properties props = new java.util.Properties();
			props.setProperty("user",args[0]);
			props.setProperty("password",args[1]);
			conn = DriverManager.getConnection("jdbc:postgresql:COMPANY",props);
		}
		catch( Exception e )
		{
			try
			{
				Class.forName("org.sqlite.JDBC");
				conn = DriverManager.getConnection("jdbc:sqlite:company.db");
			}
			catch( Exception e2 )
			{
				conn = DriverManager.getConnection("jdbc:odbc:COMPANY");
			}
		}

		String ssn, lname;
		double salary;
		String stmt1 = "select Lname, Salary from EMPLOYEE where ssn = ?";
		PreparedStatement p = conn.prepareStatement(stmt1);
		System.out.print("Enter a Social Security Number: ");
		Scanner scanner = new Scanner(System.in);
		ssn = scanner.nextLine();
		p.clearParameters();
		p.setString(1,ssn);
		ResultSet r = p.executeQuery();
		while( r.next() )
		{
			lname = r.getString(1);
			salary = r.getDouble(2);
			System.out.println(lname+" "+salary);
		}
		r.close();
		conn.close();
	}
}
