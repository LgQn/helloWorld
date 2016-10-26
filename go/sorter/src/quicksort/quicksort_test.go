package quicksort

import "testing"

func Testquicksort (t *testing.T) {
    values := []int{ 5, 4, 3, 2, 1, 0 }
    Quicksort(values)
    if values[0] != 1 || values[1] != 2 || values[2] != 3 || values[3] != 4 || values[4] != 5 {
        t.Error("Quicksort() failed. Got", values, "Expected 1 2 3 4 5")
    }
}
