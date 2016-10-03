import java.io.*;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class InsertServlet
 */
@WebServlet("/InsertServlet")
public class InsertServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public InsertServlet() {
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
		C2011004095 ts = new C2011004095();
		
		request.setCharacterEncoding("utf-8");
	    response.setContentType("text/html;charset=utf-8");
	    PrintWriter out = response.getWriter();
	    
		long nowmills = System.currentTimeMillis();
		
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String now = sdf.format(new Date(nowmills));
		
		out.println("<html><head><title>DBS WEB BOARD</title></head><body>");
		out.println("<br></br>");
		out.println("<h3 style=\"text-align:center\">"+now+"</h3>");
		
		try{
			String strTitle = request.getParameter("title");
			String strWriter = request.getParameter("writer");
			String strContent = request.getParameter("content");
			String strPsw = request.getParameter("psw");
			
			if(strTitle==""||strWriter==""||strPsw==""){
				out.println("<br></br>");
				out.println("<br></br>");
				out.println("<br></br>");
				out.println("<h2 style=\"text-align:center\">입력되지 않은 정보가 있습니다.</h2>");
				out.println("<br></br>");
				out.println("<h3 align=center><a href=\"./WriteServlet\">뒤로 가기</a></h3>");
				out.println("<br></br><br></br><br></br><br></br></body></html>");
			}
			else{
				out.println("<br></br>");
				out.println("<br></br>");
				out.println("<br></br>");
				out.println("<h2 style=\"text-align:center\">잠시만 기다려주십시오.</h2>");
				out.println("<br></br><br></br><br></br><br></br></body></html>");
				
			
				Class.forName("com.mysql.jdbc.Driver").newInstance();
				
				String url = "jdbc:mysql://localhost:3306/D2011004095?characterEncoding=UTF-8";
				String user = "root";
				String psw = "123456";
				Connection con = DriverManager.getConnection(url, user, psw);
				
				Statement stmt = con.createStatement();
				String sql = "INSERT INTO maintext(title, m_writer, m_date, m_content, password) VALUES('"+strTitle+"', '"+strWriter+"', '"+now+"', '"+strContent+"', '"+strPsw+"')";
				stmt.executeUpdate(sql);
				stmt.close();
				con.close();
				response.sendRedirect("./C2011004095");
			}
		} catch(Exception e){
			e.printStackTrace();
		}
	}

}