public class Gamer
{
    static final String url = "jdbc:sqlite:movies.db";
	public static void main(String[] args) throws Exception
	{
	    java.sql.Connection conn = java.sql.DriverManager.getConnection(url);
		java.sql.Statement stmt = conn.createStatement();

		java.sql.ResultSet rs = stmt.executeQuery(
		    "SELECT starName " +
			"FROM StarsIn " +
			"GROUP BY starName " +
			"ORDER BY COUNT(DISTINCT movieTitle, movieYear) " +
			"DESC LIMIT 1");

		while (rs.next())
		{
		    System.out.println(rs.getString(1));
		}
		rs.close();
		conn.close();
	}
}
