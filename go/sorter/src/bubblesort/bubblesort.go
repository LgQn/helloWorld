package bubblesort

func bubblesort(values []int, p int) {
    for i := 0; i < p; i ++ {
        if values[i] > values[p] {
            values[i], values[p] = values[p], values[i]
        }
    }
    if p > 0 {
        bubblesort(values, p - 1)
    }
}

func Bubblesort(values []int) {
    bubblesort(values, len(values) - 1)
}
