package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

var out [][]int

var tree []struct {
	first  []int
	second int
}

var mark []bool
var markTree []bool

var mother_vector_xd []int

var first []int
var second []int

var f_size int
var s_size int

func solve(i int) {
	mother_vector_xd = append(mother_vector_xd, i)
	f_size--
	for _, j := range tree[i].first {
		if f_size == s_size {
			first = append(first, j)
		} else if f_size-tree[j].second < s_size+tree[j].second {
			solve(j)
		} else if f_size-tree[j].second >= s_size+tree[j].second {
			f_size -= tree[j].second
			s_size += tree[j].second
			second = append(second, j)
		}
	}
}

func print_answer(w *bufio.Writer, vector1 *[]int, j int) {
	w.WriteString(strconv.Itoa(j+1) + " ")
	for _, i := range tree[j].first {
		print_answer(w, vector1, i)
	}
}

func dfs(v int) {
	mark[v] = true
	for _, u := range out[v] {
		if !mark[u] {
			tree[v].first = append(tree[v].first, u)
			tree[v].second = 1
			dfs(u)
		}
	}
	markTree[v] = true
	for _, i := range tree[v].first {
		if tree[i].second == 0 {
			tree[i].second++
		}
		tree[v].second += tree[i].second
	}
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	scanner.Split(bufio.ScanWords)

	scanner.Scan()
	c, _ := strconv.Atoi(scanner.Text())
	scanner.Scan()
	t, _ := strconv.Atoi(scanner.Text())

	out = make([][]int, c)
	tree = make([]struct {
		first  []int
		second int
	}, c)
	mark = make([]bool, c)
	markTree = make([]bool, c)

	for i := 0; i < t; i++ {
		scanner.Scan()
		a, _ := strconv.Atoi(scanner.Text())
		scanner.Scan()
		b, _ := strconv.Atoi(scanner.Text())
		a--
		b--
		out[a] = append(out[a], b)
		out[b] = append(out[b], a)
	}

	dfs(0)
	f_size = len(tree)
	solve(0)

	writer.WriteString(fmt.Sprintf("%d %d\n", len(mother_vector_xd), f_size))
	for _, i := range mother_vector_xd {
		writer.WriteString(strconv.Itoa(i+1) + " ")
	}
	writer.WriteString("\n")
	for _, i := range first {
		print_answer(writer, &first, i)
	}
	writer.WriteString("\n")
	for _, i := range second {
		print_answer(writer, &second, i)
	}
	writer.WriteString("\n")
}
