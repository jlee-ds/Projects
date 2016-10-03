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
 * Servlet implementation class ModifyServlet
 */
@WebServlet("/ModifyServlet")
public class ModifyServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ModifyServlet() {
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
		request.setCharacterEncoding("utf-8");
	    response.setContentType("text/html;charset=utf-8");
	    PrintWriter out = response.getWriter();

	    out.println("<html><head><title>DBS WEB BOARD</title></head><body>");
	    out.println("<br></br><br></br>");
	    out.println("<br></br><br></br>");
	    try{
	    	String m_id = request.getParameter("id");
	    	String psw = request.getParameter("psw");
	    	String strTitle = request.getParameter("title");
			String strWriter = request.getParameter("writer");
			String strContent = request.getParameter("content");
	    	
	    	String realpsw="";
	    	
	    	Class.forName("com.mysql.jdbc.Driver").newInstance();
			
			String url = "jdbc:mysql://localhost:3306/D2011004095?characterEncoding=UTF-8";
			String user = "root";
			String password = "123456";
			Connection con = DriverManager.getConnection(url, user, password);
			
			Statement stmt = con.createStatement();
			String sql = "SELECT password FROM maintext WHERE m_id="+m_id;
			ResultSet rs = stmt.executeQuery(sql);
			while(rs.next()){
				realpsw = rs.getString(1);
			}
			
			if(realpsw.compareTo(psw)==0){
				out.println("<h2 align=center>"+m_id+"번 글이 수정됩니다.</h2>");
				sql = "UPDATE maintext SET title='"+strTitle+"', m_writer='"+strWriter+"', m_content='"+strContent+"' WHERE m_id="+m_id;
				stmt.executeUpdate(sql);
				rs.close();
				stmt.close();
				con.close();
				response.sendRedirect("./ContentServlet?id="+m_id+"");
			}else{
				out.println("<h2 align=center>비밀번호가 틀렸습니다!</h2>");
				out.println("<h3 align=center><a href=\"./ContentServlet?id="+m_id+"\">돌아가기</a></h3>");
				rs.close();
				stmt.close();
				con.close();
			}
			
			
	    } catch (Exception e) {
	    	e.printStackTrace();
	    }
	}

}