import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class PasswordServlet
 */
@WebServlet("/PasswordServlet")
public class PasswordServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public PasswordServlet() {
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
	    
	    String m_id = "";
	    m_id = request.getParameter("id");

	    out.println("<html><head><title>DBS WEB BOARD</title></head><body>");
	    out.println("<br></br><br></br>");
	    out.println("<br></br><br></br>");
		out.println("<h2 style=\"text-align:center\">정말 삭제하시겠습니까?</h2>");
		out.println("<h3 style=\"text-align:center\">그렇다면 비밀번호를 입력하고 '삭제' 버튼을 누르세요.</h3>");
		out.println("<p align=center>------------------------------------------------------------------------------</p>");
		out.println("<form method=post action=DeleteServlet>");
		out.println("<input type=hidden name=id value="+m_id+">");
		out.println("<p align=center><b>비밀번호</b></p><p align=center><input type=text name=psword style=\"width:300px;font-size:20px\"  maxlength=100></p>");
		out.println("<p align=center><input type=submit name=deletebtn value=\"삭 제\" style=\"height:50px; width:100px; font-size:30px; \"></p></form>");
		out.println("<br></br><br></br><br></br><br></br></body></html>");
	}

}