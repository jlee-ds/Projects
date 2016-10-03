% robust_estimate_essential_matrix.m

function [E, inliers] = robust_estimate_essential_matrix(pts0, pts1, inlier_thr, prob)

	n = size(pts0);
	n = n(2);					% total point number.

	ransacTry = Inf;			% 처음엔 란삭 알고리즘을 무한번 돌린다.
	k=1;						
	inlier_num = 0;				% 인라이어 갯수는 0으로 초기화.

	while k <= ransacTry
		
		randindex = randperm(n);		
		randindex = randindex(1,1:7);	%7개의 점을 중복되지 않게 뽑아.

		for i = 1:7,
			tmpx0(:,i) = pts0(:,randindex(i));  
			tmpx1(:,i) = pts1(:,randindex(i));  %tmpx0, tmpx1을 만든 뒤.
		end;
 
		candidate_E = estimate_essential_matrix(tmpx0, tmpx1);
		numE = size(candidate_E);
		numE = numE(3);						% estimate_essential_matrix를 만든다.

		for i = 1:numE,					%에센셜 매트릭스 갯수 만큼.
			inlier_count = 0;
			for j = 1:n,				%모든 점에 대해.
				l1 = candidate_E(:,:,i)*pts0(:,j);
				thr = pts1(:,j)'*l1;
				thr = thr/sqrt(l1(1)^2+l1(2)^2);			
				if thr < inlier_thr,
					inlier_count = inlier_count + 1;
					tmp_inliers(inlier_count) = j;		%inlier의 갯수와 index를 저장한다.
				end;
			end;
			if inlier_count > inlier_num,    		%inlier갯수가 기존의 것 보다 많다면,
				E = candidate_E(:,:,i)				
				inliers = tmp_inliers
				inlier_num = inlier_count			%essential matrix와 inlier index와 inlier number를 최신으로 바꿔준다.
				p = inlier_num/n;
				S = log10(1-prob)/log10(1-p^7);			%현재 inlier갯수로 해당 확률을 충족시키려면 몇번의 알고리즘을 더 돌려야 하는 지 계산한다.
				if S == -Inf,						%너무 많이 돌려야하면 그냥 계속 inf 돌게 냅두고
					%k = 1;
				else
					%k = 1;
					ransacTry = ceil(S)					%그게 아니라면 새로 업데이트. 돌아야할 횟수를.
				end;
			else
			end;
			tmp_inliers = zeros(size(tmp_inliers));
		end;
		k = k + 1;
	end;


end