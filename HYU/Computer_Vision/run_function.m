% run_hw2

n = 100;
n_outlier = 10;
noise = 0.01;
ransac_prob = 0.999;
inlier_thr = 0.01;

[x0, x1, p, P] = generate_data(n, n_outlier, noise);

subplot('position', [0, 0, 0.7, 1]);
plot3(p(1,:), p(2,:), p(3,:), '.');
hold on;
plot_camera([], 'r');
plot_camera(P, 'g');
hold off;
axis equal
view(0, 20);

subplot('position', [0.7, 0.05, 0.3, 0.4]);
plot(x0(1,:), x0(2,:), 'r.');
title('img0');
axis equal;

subplot('position', [0.7, 0.55, 0.3, 0.4]);
plot(x1(1,:), x1(2,:), 'g.');
title('img1');
axis equal;

[E_est, inliers] = robust_estimate_essential_matrix(x0, x1, inlier_thr, ransac_prob);
% RANSAC (use randperm to generate samples).