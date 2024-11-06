function Square( n: int ): int
{
	n*n
}

function SumInts( n: int ): int
	requires n >= 0
	decreases n
{
	if n == 0 then 0 else SumInts(n-1)+n
}

function SumCubes( n: int ): int
	requires n >= 0
	decreases n
	ensures SumCubes(n) == Square(SumInts(n))
{
	if n == 0 then 0 else SumCubes(n-1)+n*n*n
}

