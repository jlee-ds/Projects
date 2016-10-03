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

@WebServlet("/C2011004095")
public class C2011004095 extends HttpServlet {
	
	static boolean hitorder = false;
	static int currentpagenum=1;
	static int currenttextnum;
	static boolean searchflag = false;
	static String searchword;
	
	public int GetCurrentNum(){
		return currentpagenum;
	}
	
	public void SetCurrentNum(int num){
		currentpagenum = num;
	}
	
	public int GetTotalNum(){
		return currenttextnum;
	}
	
	public void SetTotalNum(int num){
		currenttextnum = num;
	}
	
	public void SetHitorder(boolean hitorder){
		this.hitorder = hitorder;
	}
	
	public boolean GetHitorder(){
		return hitorder;
	}
	
	public C2011004095(){
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
			rs.close();
			stmt.close();
			con.close();
		} catch (Exception e) {
			e.getStackTrace();
		}
	}

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doPost(request, response);
	}
	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		   
		request.setCharacterEncoding("utf-8");
	    //String menu[]=request.getParameterValues("menu");
		int countten=0;
		int i=0;

	    response.setContentType("text/html;charset=utf-8");
	    PrintWriter out = response.getWriter();
	    out.println("<html><head><title>DBS WEB BOARD</title></head><body>");
	    out.println("<br></br>");
	    out.println("<br></br>");
	    out.println("<h1 style=\"text-align:center\">DATABASE SYSTEM TERM PROJECT</h1>");
	    out.println("<h2 style=\"text-align:center\">간단한 웹 게시판 만들기</h2>");
	    out.println("<h4 style=\"text-align:center\">WITH : JAVA SERVLET + JDBC + HTML + MYSQL + TOMCAT</h4>");
	    out.println("<br></br>");
	    out.println("<form method=post action=SearchServlet>");
	    out.println("<table width=930 align=center><tr>");
	    if(hitorder == false){
	    	out.println("<td><p align=right><a href=\"./WriteServlet\">새로운 글 쓰기</a> | ");
	    	out.println("<a href=\"./HitOrderServlet\">조회수로 정렬</a> | ");
	    }else{
	    	out.println("<td><p align=right><a href=\"./WriteServlet\">새로운 글 쓰기</a> | ");
	    	out.println("<a href=\"./HitOrderServlet\">등록일로 정렬</a> | ");
	    }
    	out.println("<input type=text name=keyword size=30  maxlength=50> <input type=submit value=\"검색\">");
    	out.println("</p></td></tr></table></form>");
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
			String forsearch = "";
			if(searchflag==true)
				forsearch = "WHERE title='%"+searchword+"%'";
			if(hitorder==false)
				sql = "SELECT * FROM maintext "+forsearch+" ORDER BY m_id desc";
			else
				sql = "SELECT * FROM maintext "+forsearch+" ORDER BY hits desc, m_id desc";
			ResultSet rs = stmt.executeQuery(sql);
			while(rs.next()&&countten!=10){
				i++;
				//System.out.println(currentpagenum);
				if(currentpagenum*10-9<=i){
					out.println("<tr><td width=70><p align=center>"+rs.getInt(1)+"</p></td>");
				    out.println("<td width=450><p align=center><a href=\"./ContentServlet?id="+rs.getInt(1)+"\">"+rs.getString(2)+"</a></p></td>");
				    out.println("<td width=120><p align=center>"+rs.getString(3)+"</p></td>");
				    out.println("<td width=200><p align=center>"+rs.getDate(4)+"</p></td>");
				    out.println("<td width=100><p align=center>"+rs.getInt(5)+"</p></td></tr>");
				    countten++;
				}
			}
			rs.close();
			stmt.close();
			con.close();
		} catch (Exception e){
			e.printStackTrace();
		}
	    out.println("</table>");
	    out.println("<p align=center><a href=\"./MinusListNumServlet\">이전</a> | ");
	    out.println("<a href=\"./PlusListNumServlet\">다음</a></p>");

	   
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
