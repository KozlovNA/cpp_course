#include <algorithm>
#include <cassert>
#include <vector>

struct Point {
  double x = 0, y = 0;
};

struct Rectangle {
  Point left_upper_corner, right_lower_corner;
};

auto area(Rectangle const &rec) {
  return std::abs(rec.left_upper_corner.x - rec.right_lower_corner.x) *
         std::abs(rec.left_upper_corner.y - rec.right_lower_corner.y);
}

auto intersection_area(Rectangle const &rec1, Rectangle const &rec2,
                       double epsilon) {
  Point luc(std::max(rec1.left_upper_corner.x, rec2.left_upper_corner.x),
            std::max(rec1.left_upper_corner.y, rec2.left_upper_corner.y));
  Point rlc(std::min(rec1.right_lower_corner.x, rec2.right_lower_corner.x),
            std::min(rec1.right_lower_corner.y, rec2.right_lower_corner.y));
  Rectangle inter(luc, rlc);
  if ((luc.x + epsilon < rlc.x) && (luc.y + epsilon < rlc.y)) {
    return area(inter);
  } else if (std::abs(luc.x - rlc.x) < epsilon) {
    return 0.0;
  } else {
    return -1.0;
  }
}

auto intersection_area_test_template(double luc1_x, double luc1_y,
                                     double rlc1_x, double rlc1_y,
                                     double luc2_x, double luc2_y,
                                     double rlc2_x, double rlc2_y,
                                     double result) {
  Point luc1(luc1_x, luc1_y);
  Point rlc1(rlc1_x, rlc1_y);
  Rectangle rec1(luc1, rlc1);

  Point luc2(luc2_x, luc2_y);
  Point rlc2(rlc2_x, rlc2_y);
  Rectangle rec2(luc2, rlc2);

  assert(intersection_area(rec1, rec2, 1e-8) == result);
}

auto intersection_area_test() {
  intersection_area_test_template(0, 0, 1, 1, 0.5, 0.5, 1.5, 1.5, 0.25);
  intersection_area_test_template(0, 0, 1, 1, 1.5, 1.5, 2.0, 2.0, -1.0);
  intersection_area_test_template(0, 0, 1, 1, 1.0, 0.5, 2.0, 2.0, 0.0);
}

[[nodiscard]] auto
minimal_restricting_rect(std::vector<Rectangle> const &vec_of_rect) {
  double min_luc_x = vec_of_rect[0].left_upper_corner.x;
  double min_luc_y = vec_of_rect[0].left_upper_corner.y;
  double max_rlc_x = vec_of_rect[0].right_lower_corner.x;
  double max_rlc_y = vec_of_rect[0].right_lower_corner.y;
  for (Rectangle const &rec : vec_of_rect) {
    min_luc_x = std::min(rec.left_upper_corner.x, min_luc_x);
    min_luc_y = std::min(rec.left_upper_corner.y, min_luc_y);
    max_rlc_x = std::max(rec.right_lower_corner.x, max_rlc_x);
    max_rlc_y = std::max(rec.right_lower_corner.y, max_rlc_y);
  }
  Point luc(min_luc_x, min_luc_y);
  Point rlc(max_rlc_x, max_rlc_y);
  Rectangle rec(luc, rlc);
  return rec;
}

auto minimal_restricting_rect_test() {
  std::vector<double> luc_x{0, 0.5, 1.5, 1.0};
  std::vector<double> luc_y{0, 0.5, 1.5, 0.5};
  std::vector<double> rlc_x{1, 1.5, 2.0, 2.0};
  std::vector<double> rlc_y{1, 1.5, 2.0, 2.0};
  std::vector<Rectangle> vec_of_rect;
  for (std::size_t i = 0; i < luc_x.size(); i++) {
    Point luc(luc_x[i], luc_y[i]);
    Point rlc(rlc_x[i], rlc_y[i]);
    Rectangle rec(luc, rlc);
    vec_of_rect.push_back(rec);
  }
  Rectangle restricting_rec = minimal_restricting_rect(vec_of_rect);
  double epsilon = 1e-8;
  assert(std::abs(restricting_rec.left_upper_corner.x - 0) < epsilon &&
         std::abs(restricting_rec.left_upper_corner.y - 0) < epsilon &&
         std::abs(restricting_rec.right_lower_corner.x - 2.0) < epsilon &&
         std::abs(restricting_rec.right_lower_corner.y - 2.0) < epsilon);
}

int main() {
  intersection_area_test();
  minimal_restricting_rect_test();

  return 0;
}
