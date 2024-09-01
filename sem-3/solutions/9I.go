package main

import (
	"bufio"
	"fmt"
	"os"
)

const (
	N   = 60000
	mod = 1e9 + 7
)

var (
	n, d, ans, length int
	depth             [N + 1]int
	sn                [N + 1][10]int
	fail              [N + 1]int
	dp                [51][N + 1][2][2][2]int
	s, tx, ty         string
)

func adder(x *int, d int) {
	*x += d
	if *x >= mod {
		*x -= mod
	}
}

func boolToInt(b bool) int {
	if b {
		return 1
	}
	return 0
}

func build() {
	var q []int
	for i := 0; i <= 9; i++ {
		if sn[0][i] != 0 {
			depth[sn[0][i]] = 1
			q = append(q, sn[0][i])
		}
	}
	for len(q) > 0 {
		top := q[0]
		q = q[1:]
		for i := 0; i <= 9; i++ {
			if sn[top][i] != 0 {
				depth[sn[top][i]] = depth[top] + 1
				fail[sn[top][i]] = sn[fail[top]][i]
				q = append(q, sn[top][i])
			} else {
				sn[top][i] = sn[fail[top]][i]
			}
		}
	}
}

func main() {
	r := bufio.NewReader(os.Stdin)
	fmt.Fscan(r, &s, &tx, &ty)
	n, d = len(s), len(tx)

	for i := 1; i <= n-(d>>1)+1; i++ {
		x := 0
		for j := i; j <= i+(d>>1)-1; j++ {
			if sn[x][s[j-1]-'0'] == 0 {
				length++
				sn[x][s[j-1]-'0'] = length
			}
			x = sn[x][s[j-1]-'0']
		}
	}

	build()
	dp[0][0][0][0][0] = 1

	for i := 1; i <= d; i++ {
		for j := 0; j <= length; j++ {
			for op := 0; op <= 1; op++ {
				for op2 := 0; op2 <= 1; op2++ {
					for opt := 0; opt <= 1; opt++ {
						for k := 0; k <= 9; k++ {
							if op == 0 && k < int(tx[i-1]-'0') {
								continue
							}
							if op2 == 0 && k > int(ty[i-1]-'0') {
								continue
							}
							adder(&dp[i][sn[j][k]][op|boolToInt(k > int(tx[i-1]-'0'))][op2|boolToInt(k < int(ty[i-1]-'0'))][opt|boolToInt(depth[sn[j][k]] >= (d>>1))], dp[i-1][j][op][op2][opt])
						}
					}
				}
			}
		}
	}

	for i := 0; i <= length; i++ {
		for op := 0; op <= 1; op++ {
			for op2 := 0; op2 <= 1; op2++ {
				adder(&ans, dp[d][i][op][op2][1])
			}
		}
	}

	fmt.Printf("%d\n", ans)
}
