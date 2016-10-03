import java.io.IOException;
import java.io.PrintWriter;
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
 * Servlet implementation class ContentServlet
 */
@WebServlet("/ContentServlet")
public class ContentServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ContentServlet() {
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
		int hits;
		String [] contentarray;
		
		request.setCharacterEncoding("utf-8");
		   
	    response.setContentType("text/html;charset=utf-8");
	    PrintWriter out = response.getWriter();
	    
	    String m_id = request.getParameter("id");
	    System.out.println(m_id);
	    
	    out.println("<html><head><title>DBS WEB BOARD</title></head><body>");
	    out.println("<br></br>");
	    out.println("<br></br>");
	    out.println("<h2 style=\"text-align:center\">"+m_id+"번 게시글 보기</h2>");
	    out.println("<br></br>");
	    try{
	    	
	    	Class.forName("com.mysql.jdbc.Driver").newInstance();
			
			String url = "jdbc:mysql://localhost:3306/D2011004095?characterEncoding=UTF-8";
			String user = "root";
			String psw = "123456";
			Connection con = DriverManager.getConnection(url, user, psw);
			
			Statement stmt = con.createStatement();
			String sql = "SELECT * FROM maintext WHERE m_id="+m_id;
			ResultSet rs = stmt.executeQuery(sql);
			while(rs.next()){
				out.println("<table align=center cellspacing=1 border=1 cellpadding=3>");
			    out.println("<tr><td width=100><p align=center><b>제 목</b></p></td><td width=500><p align=left></p>"+rs.getString(2)+"</td></tr>");
			    out.println("<tr><td width=100><p align=center><b>작성자</b></p></td><td width=500><p align=left></p>"+rs.getString(3)+"</td></tr>");
			    out.println("<tr><td width=100><p align=center><b>작성일</b></p></td><td width=500><p align=left></p>"+rs.getDate(4)+" | "+rs.getTime(4).getHours()+":"+rs.getTime(4).getMinutes()+"</td></tr>");
			    hits = rs.getInt(5);
			    hits++;
			    out.println("<tr><td width=100><p align=center><b>조회수</b></p></td><td width=400><p align=left></p>"+hits+"</td></tr>");
			    contentarray = rs.getString(6).split("\n");
			    out.println("<tr><th colspan=2 width=600><textarea readonly=\"readonly\" style=\"height:450px;width:600px;font-size:15px\">");
			    out.println(""+rs.getString(6)+"");
			    out.println("</textarea></th></tr>");
			    out.println("</table>");
			    sql = "UPDATE maintext set hits="+hits+" WHERE m_id="+m_id;   
			}
			stmt.executeUpdate(sql);
			out.println("<table align=center width=600>");
			out.println("<tr><td><p align=right><a href=\"./C2011004095\">목록으로</a> | ");
			out.println("<a href=\"./WriteServlet?id="+m_id+"&modify=1\">수정하기</a> | ");
		    out.println("<a href=\"./PasswordServlet?id="+m_id+"\">지우기</a></p></td></tr></table");
		    out.println("<br></br>");
		    out.println("<table align=center width=750>");
			out.println("<tr><td><p align=left><b>짧은 답 글 달기 :</b>");
		    out.println("</p></td></tr></table>");
		    out.println("<form method=post action=CommentServlet>");
		    out.println("<input type=hidden name=id value="+m_id+">");
		    out.println("<table align=center cellspacing=1 border=1><tr>");
			out.println("<td> <input type=\"text\" name=\"comment\" style=\"width:500px;font-size:15px\"  maxlength=256> </td>");
			out.println("<td>이름 : <input type=\"text\" name=\"c_writer\" style=\"width:100px;font-size:15px\"  maxlength=20> </td>");
			out.println("<td><input type=\"submit\" name=\"commentbtn\" value=\"제  출\" style=\"width:100px;font-size:30px\"></td>");
			out.println("</tr></table></form>");
			out.println("<br></br>");
			out.println("<table align=center cellspacing=1 border=1 cellpadding=3><tr>");
			out.println("<td width=500><p align=center style=\"font-size:18px\"><b>"+m_id+"번 글에 달려 있는 짧은 답 글들</b></td>");
			out.println("<td width=100><p align=center style=\"font-size:18px\"><b>작성자</b></td>");
			out.println("<td width=200><p align=center style=\"font-size:18px\"><b>날 짜</b></td></tr>");
			sql = "SELECT * FROM comment WHERE m_id="+m_id+" ORDER BY c_id desc";
			rs = stmt.executeQuery(sql);
			while(rs.next()){
			    out.println("<tr><td width=500><p align=left>"+rs.getString(4)+"</p></td>");
			    out.println("<td width=100><p align=center>"+rs.getString(2)+"</p></td>");
			    out.println("<td width=200><p align=center>"+rs.getDate(3)+" | "+rs.getTime(3).getHours()+":"+rs.getTime(3).getMinutes()+"</p></td></tr>");
			    
			}
			out.println("</table>");
			out.println("<br></br><br></br><br></br><br></br></body></html>");
			rs.close();
		    stmt.close();
			con.close();
	    } catch (Exception e) {
	    	e.printStackTrace();
	    }
	}

}