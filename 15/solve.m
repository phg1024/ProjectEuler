% consider the ways of getting to grid point as F(i, j)
% F(0, i) = F(j, 0) = 0
% F(1, 1) = 1
% F(1, 2) = 1, F(2, 1) = 1
% F(1, 3) = 1, F(2, 2) = 2, F(3, 1) = 1
% F(i, j) = F(i-1, j) + F(j-1, i)

% turns out this is the pascal triangle, and the solution for a n-by-n
% grid is F(n, n) = nchoosek( 2*n, n )

function solve( n )
	fprintf('%20d\n', nchoosek(2*n, n));
end