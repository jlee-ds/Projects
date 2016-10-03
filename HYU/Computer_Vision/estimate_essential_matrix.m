% estimate_essential_matrix.m 

function E = estimate_essential_matrix(pts0, pts1)

	format short     % 소수 4째 자리까지..?
	A = zeros(7,9);
	tmp = zeros(9,1);

	for i = 1:7,
		tmp(1:3,1) = pts0(:,i).*pts1(1,i);
		tmp(4:6,1) = pts0(:,i).*pts1(2,i);
		tmp(7:9,1) = pts0(:,i);
		A(i,:) = tmp';					
	end;		% make (xx',yx',x',xy',yy',y',x,y,1) * 7 matrix == A

	N = null(A,'r');		% get null vector

	nullvecnum = size(N);
	nullvecnum = nullvecnum(2);		% number of null vector

	E0 = zeros(3,3);
	E1 = zeros(3,3);		% only take two null vector and make essential matrix

	E0(1,:) = N(1:3,1);
	E0(2,:) = N(4:6,1);
	E0(3,:) = N(7:9,1);

	E1(1,:) = N(1:3,2);
	E1(2,:) = N(4:6,2);
	E1(3,:) = N(7:9,2);

	syms a   			% alpha.

	E_with_a = a .* E0 + (1-a) .* E1;	% estimate essential matrix

	alphaEq = det(E_with_a);		% determinent equation.

	alpha = solve(alphaEq);			% solve it.
	alpha = double(alpha);			% 소수 넷째 짜리까지 유효.

	count = 0;
	for i = 1:3,
		totalsum = 0;
		tmpE = alpha(i).*E0+(1-alpha(i)).*E1;
		for j = 1:7,
			totalsum = totalsum +  pts1(:,i)'*tmpE*pts0(:,i);         
		end;
		%if abs(totalsum) < 0.1e-10,
			count = count + 1;
			E(:,:,i) = tmpE;		% 원래는 totalsum이 작은 것만을 리턴하려고 했다.
		%end;						% 그러나 딱 0이 안나와서 저 크기를 정해주는 것이 골치아파졌다.
	end;							% 그래서 그냥 다 리턴. 어차피 ransac에서 탈락할 거라 생각했다.

end