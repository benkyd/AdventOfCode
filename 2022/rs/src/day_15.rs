
pub const CHALLENGE_INPUT: &str = include_str!("../15.input");
pub const EXAMPLE_INPUT: &str = "498,4 -> 498,6 -> 496,6\n503,4 -> 502,4 -> 502,9 -> 494,9"; 


pub fn part_1(input: &str) -> i32 {
    return 1;
}

pub fn part_2(input: &str) -> i32 {
    return 1;
}

#[cfg(test)]
mod test {
    use crate::day_15;

    #[test]
    fn part1_test() {
        assert_eq!(day_15::part_1(day_15::EXAMPLE_INPUT), 24);
        assert_eq!(day_15::part_1(day_15::CHALLENGE_INPUT), 757);
    }

    #[test]
    fn part2_test() {
        assert_eq!(day_15::part_2(day_15::EXAMPLE_INPUT), 93);
        assert_eq!(day_15::part_2(day_15::CHALLENGE_INPUT), 24943);
    }
}

