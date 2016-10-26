package quicksort


func quicksort(values []int, left, right int) {
    temp := values[left]
    p := left
    i, j := left, right

    for i < j {
        for values[j] >= temp && p < j {
            j --
        }

        if p < j {
            values[p] = values[j]
            p = j
        }

        for values[i] <= temp && i < p {
            i ++
        }

        if i < p {
            values[p] = values[i]
            p = i
        }
    }
    values[p] = temp


    if p - left > 1 {
        quicksort(values, left, p - 1)
    }

    if right - p > 1 {
        quicksort(values, p + 1, right)
    }
}

func Quicksort(values []int) {
    quicksort(values, 0, len(values) - 1)
}
