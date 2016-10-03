import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class PlusListNumServlet
 */
@WebServlet("/PlusListNumServlet")
public class PlusListNumServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public PlusListNumServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doPost(request,response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		int currentpagenum = 0;
		int currenttextnum = 0;
		double i;
		C2011004095 ts = new C2011004095();
		currentpagenum = ts.GetCurrentNum();
		try{
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			
			String url = "jdbc:mysql://localhost:3306/D2011004095?characterEncoding=UTF-8";
			String user = "root";
			String psw = "123456";
			Connection con = DriverManager.getConnection(url, user, psw);
			
			Statement stmt = con.createStatement();
			String sql = "SELECT COUNT(*) FROM maintext";
			ResultSet rs = stmt.executeQuery(sql);
			while(rs.next()){
				currenttextnum = rs.getInt(1);
			}
			rs.close(); stmt.close(); con.close();
		}catch(Exception e){
			e.printStackTrace();
		}
		ts.SetTotalNum(currenttextnum);
		i = Math.ceil((double)currenttextnum/10);
		if(currentpagenum<i)
			currentpagenum++;
		System.out.println(currentpagenum);
		ts.SetCurrentNum(currentpagenum);
		response.sendRedirect("./C2011004095");
	}

}