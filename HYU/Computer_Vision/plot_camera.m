% plot_camera.m

function plot_camera(P, c)

	if nargin < 2, c = 'ro'; end;
	if nargin < 1 || isempty(P), P = [1, 0, 0, 0; 0, 1, 0, 0; 0, 0, 1, 0]; end;

	R = P(1:3, 1:3);
	t = P(:,4);

	axis0 = 0.1 * [1, 0, 0; 0, 0, 0; 0, 1, 0; 0, 0, 0; 0, 0, 1]';
	axis = [R', -R' * t] * [axis0; ones(1, 5)];
	plot3(axis(1,:), axis(2,:), axis(3,:), c);

end