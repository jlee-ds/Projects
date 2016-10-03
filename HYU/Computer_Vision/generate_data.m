% generate_data.m

function [x0, x1, p, P] = generate_data(n, n_outlier, noise, P)

	if nargin < 2, n_outlier = 0; end;
	if nargin < 3, noise = 0.0; end;

	if nargin < 4
		th_z = rand(1) * 0.3 - 0.3;
		P = zeros(3, 4);
		P(1:3, 1:3) = eye(3);  % Identity transform.
		
		P(3,3) = cos(th_z);
		P(1,3) = -sin(th_z);
		P(1,1) = cos(th_z);
		P(3,1) = sin(th_z);
		P(:,4) = (rand(3, 1) + [-1.0; -0.5; -0.5]) .* [1.0; 0.2; 0.2];
	end

	p = rand(3, n) + repmat([-0.5, -0.5, 1.0]', [1, n]);
	q = P * [p; ones(1, n)];

	x0 = p ./ repmat(p(3,:), [3, 1]);
	x1 = q ./ repmat(q(3,:), [3, 1]); 

	x0(1:2,:) = x0(1:2,:) + randn(2, n) * noise;
	x1(1:2,:) = x1(1:2,:) + randn(2, n) * noise;

	if n_outlier > 0
	  	idx = (n - n_outlier + 1) : n;
	  	x0(1:2, idx) = 2 * (rand(2, n_outlier) - repmat([0.5; 0.5], [1, n_outlier]));
	  	x1(1:2, idx) = 2 * (rand(2, n_outlier) - repmat([0.5; 0.5], [1, n_outlier]));
	end

end