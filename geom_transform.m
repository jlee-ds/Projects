function img_out = geom_transform(img_in, param)

	ssx = size(img_in)
	ssy = ssx(1)
	ssx = ssx(2)		%to know size of image.	

	spx = [1, 1, ssx, ssx]
	spy = [1, ssy, 1, ssy]	%to set start point of input image.

	option = size(param)
	option = option(2)	%to know what transform we do. option number means the number of parameter.
	
	switch(option)
		case 2,  	%translation
			H = [1, 0, param(1); 0, 1, param(2); 0, 0, 1]
		case 3,  	%euclidean
			H = [cos(param(3)), -sin(param(3)), param(1); sin(param(3)), cos(param(3)), param(2); 0, 0, 1]	
		case 4, 	%similarity
			H = [param(4)*cos(param(3)), param(4)*-sin(param(3)), param(1); param(4)*sin(param(3)), param(4)*cos(param(3)), param(2); 0, 0, 1]	
		case 6, 	%affine
			H = [param(1), param(2), param(3); param(4), param(5), param(6); 0, 0, 1]
		case 9,  	%projective
			H = [param(1), param(2), param(3); param(4), param(5), param(6); param(7), param(8), param(9)]
	end				%to make transformation matrix H.

	for i = 1:4, 	
		tmp = H * [spx(i), spy(i), 1]';
		tmp = tmp/tmp(3);
		tpx(i) = tmp(1)
		tpy(i) = tmp(2)		%to know transformed point of transformed image. (four point)
	end; 		

	minx = spx(1);
	maxx = spx(1);
	miny = spy(1);
	maxy = spy(1);			%to set beginning value of min and max.

	for i = 1:4,
		if minx > spx(i), minx = spx(i);, end
		if minx > tpx(i), minx = tpx(i);, end
		if maxx < spx(i), maxx = spx(i);, end 
		if maxx < tpx(i), maxx = tpx(i);, end 
		if miny > spy(i), miny = spy(i);, end 
		if miny > tpy(i), miny = tpy(i);, end 
		if maxy < spy(i), maxy = spy(i);, end 
		if maxy < tpy(i), maxy = tpy(i);, end 
	end;				%to find min and max of x-axis and y-axis
	
	minx = floor(minx)
	miny = floor(miny)
	maxx = ceil(maxx)
	maxy = ceil(maxy)		%to contain all color(?). i don't know well about this part.

	outsize(1) = maxy - miny + 1;
	outsize(2) = maxx - minx + 1	%to set img_out's size.

	img_out = zeros(outsize(1), outsize(2), 3);
	img_out = uint8(img_out);	%to make img_out's matrix. double to uint8 please.
	size(img_out)
	class(img_out)

	opx = 1 - minx + 1
	opy = 1 - miny + 1		%find original image's original point.

	grayimg = rgb2gray(img_in);
	img_out(opy:opy+ssy-1,opx:opx+ssx-1,1) = grayimg;
	img_out(opy:opy+ssy-1,opx:opx+ssx-1,2) = grayimg;
	img_out(opy:opy+ssy-1,opx:opx+ssx-1,3) = grayimg;	%to make gray scale image. 
		
	arcH = H^-1
	
	for i = 1:outsize(1),
		for j = 1:outsize(2),
			temp = arcH * [j-opx+1, i-opy+1, 1]';
			temp = temp/temp(3);
			ipx = temp(1);
			ipy = temp(2);
			if ipx >= 1 & ipx <= ssx & ipy >= 1 & ipy <= ssy, 
				ifpx = floor(ipx);
				ifpy = floor(ipy);
				icpx = ceil(ipx);
				icpy = ceil(ipy);
				u = ipx - ifpx;
				v = ipy - ifpy;
				for k = 1:3,
					if ipx == ifpx & ipy == ifpy,
					    img_out(i,j,k) = img_in(ifpy,ifpx,k);
					else
					    img_out(i,j,k) = uint8((1-u)*(1-v)*img_in(ifpy,ifpx,k) + u*(1-v)*img_in(ifpy,icpx,k) + (1-u)*v*img_in(icpy,ifpx,k) + u*v*img_in(icpy,icpx,k));
					end
				end;
			end
		end;
	end;

	imwrite(img_out, 'img_out.jpg')

end























