

import java.io.*;
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
 * Servlet implementation class SearchServlet
 */
@WebServlet("/SearchServlet")
public class SearchServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public SearchServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doPost(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		request.setCharacterEncoding("utf-8");
		   
	    response.setContentType("text/html;charset=utf-8");
	    PrintWriter out = response.getWriter();
	    
	    String keyword = request.getParameter("keyword");
	    System.out.println(keyword);
	    
	    out.println("<html><head><title>DBS WEB BOARD</title></head><body>");
	    out.println("<br></br>");
	    out.println("<br></br>");
	    out.println("<h2 style=\"text-align:center\">'"+keyword+"'으로 검색 결과</h2>");
	    out.println("<br></br>");
	    out.println("<table cellspacing=1 width=960 border=1 align=center cellpadding=5><tr>");
	    out.println("<td width=70><p align=center style=\"font-size:18px\"><b>번호</d></p></td>");
	    out.println("<td width=450><p align=center style=\"font-size:18px\"><b>제목</d></p></td>");
	    out.println("<td width=150><p align=center style=\"font-size:18px\"><b>게시자</b></p></td>");
	    out.println("<td width=200><p align=center style=\"font-size:18px\"><b>등록일</b></p></td>");
	    out.println("<td width=100><p align=center style=\"font-size:18px\"><b>조회수</b></p></td></tr>");
	    try{
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			
			String url = "jdbc:mysql://localhost:3306/D2011004095?characterEncoding=UTF-8";
			String user = "root";
			String psw = "123456";
			Connection con = DriverManager.getConnection(url, user, psw);
			
			Statement stmt = con.createStatement();
			String sql;
			sql = "SELECT * FROM maintext WHERE title like '%"+keyword+"%' ORDER BY m_id desc";
			ResultSet rs = stmt.executeQuery(sql);
			while(rs.next()){
					out.println("<tr><td width=70><p align=center>"+rs.getInt(1)+"</p></td>");
				    out.println("<td width=450><p align=center><a href=\"./ContentServlet?id="+rs.getInt(1)+"\">"+rs.getString(2)+"</a></p></td>");
				    out.println("<td width=120><p align=center>"+rs.getString(3)+"</p></td>");
				    out.println("<td width=200><p align=center>"+rs.getDate(4)+"</p></td>");
				    out.println("<td width=100><p align=center>"+rs.getInt(5)+"</p></td></tr>");
			}
			rs.close();
			stmt.close();
			con.close();
		} catch (Exception e){
			e.printStackTrace();
		}
	    out.println("</table>");
	    out.println("<p align=center><a href=\"./C2011004095\">돌아가기</a>");

	   
	   /* for(int i=0;i<menu.length;i++){
	    	out.printf("<br>%s", menu[i]);
	    }*/
	    out.println("<br></br>");
	    out.println("<br></br>");
	    out.println("<br></br>");
	    out.println("<br></br>");
	    out.println("</body></html>");
	}

}
