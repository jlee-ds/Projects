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
 * Servlet implementation class WriteServlet
 */
@WebServlet("/WriteServlet")
public class WriteServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public WriteServlet() {
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
	    //String menu[]=request.getParameterValues("menu");
	   
	    response.setContentType("text/html;charset=utf-8");
	    PrintWriter out = response.getWriter();
	    
	    String m_id = request.getParameter("id");
	    String modify = request.getParameter("modify");
	    
	    out.println("<html><head><title>DBS WEB BOARD</title></head><body>");
	    out.println("<br></br>");
	    out.println("<br></br>");
	    
	    
	    if(modify==null){
	    	out.println("<h3 style=\"text-align:center\">새로운 글 작성하기</h3>");
		    out.println("<br></br>");
		    out.println("<table align=center cellspacing=1 border=1>");
		    out.println("<form method=post action=InsertServlet>");
		    out.println("<tr><td width=100><p align=center><b>제목</b></p></td><td><input type=\"text\" name=\"title\" style=\"width:400px;font-size:15px\"  maxlength=100></td></tr>");
		    out.println("<tr><td width=100><p align=center><b>이름</b></p></td><td><input type=text name=writer style=\"width:400px;font-size:15px\"  maxlength=10></td></tr>");
		    out.println("<tr><th colspan=2><textarea name=content style=\"height:400px;width:500px;font-size:15px\"></textarea></th></tr>");
		    out.println("<tr><td width=100><p align=center><b>비밀번호</b></p></td><td><input type=text name=psw style=\"width:400px;font-size:15px\"  maxlength=20></td></tr>");
		    out.println("</table>");
		    out.println("<br></br>");
		    out.println("<table align=center width=500>");
		    out.println("<tr><td><center>");
	    	out.println("<input type=submit name=searchbtn value=\"등 록\" style=\"height:50px; width:100px; font-size:30px; \"></form>");
	    	
	    }else{
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
					out.println("<h3 style=\"text-align:center\">"+m_id+"번 게시글 수정하기</h3>");
				    out.println("<br></br>");
				    out.println("<table align=center cellspacing=1 border=1>");
					out.println("<form method=post action=ModifyServlet>");
					out.println("<input type=hidden name=id value="+m_id+">");
				    out.println("<tr><td width=100><p align=center><b>제목</b></p></td><td><input type=\"text\" name=\"title\" style=\"width:400px;font-size:15px\"  maxlength=100" +
				    		" value='"+rs.getString(2)+"'></td></tr>");
				    out.println("<tr><td width=100><p align=center><b>이름</b></p></td><td><input type=text name=writer style=\"width:400px;font-size:15px\"  maxlength=10" +
				    		" value='"+rs.getString(3)+"'></td></tr>");
				    out.println("<tr><th colspan=2><textarea name=content style=\"height:400px;width:500px;font-size:15px\">"+rs.getString(6)+"</textarea></th></tr>");
				    out.println("<tr><td width=100><p align=center><b>비밀번호</b></p></td><td><input type=text name=psw style=\"width:400px;font-size:15px\"  maxlength=20></td></tr>");
				    out.println("</table>");
				    out.println("<br></br>");
				    out.println("<table align=center width=500>");
				    out.println("<tr><td><center>");
			    	out.println("<input type=submit name=searchbtn value=\"수 정\" style=\"height:50px; width:100px; font-size:30px; \"></form>");
			    	
					 
				}
				
				rs.close();
			    stmt.close();
				con.close();
		    } catch (Exception e) {
		    	e.printStackTrace();
		    }
	    }
	    out.println("</center></td></tr></table>");
    	out.println("<br></br>");
	    out.println("<br></br>");
	    out.println("<br></br>");
	    out.println("<br></br>");
	    out.println("</body></html>");
	}

}