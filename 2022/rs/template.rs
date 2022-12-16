pub const CHALLENGE_INPUT: &str = include_str!("../**.input");
pub const EXAMPLE_INPUT: &str = ""; 

pub fn part_1(input: &str) -> i32 {
}

pub fn part_2(input: &str) -> i32 {
}

#[cfg(test)]
mod test {
    use crate::day;

    #[test]
    fn part1_test() {
        assert_eq!(day::part_1(day::EXAMPLE_INPUT), 1);
        assert_eq!(day::part_1(day::CHALLENGE_INPUT), 1);
    }

    #[test]
    fn part2_test() {
        assert_eq!(day::part_2(day::EXAMPLE_INPUT), 1);
        assert_eq!(day::part_2(day::CHALLENGE_INPUT), 1);
    }
}

