#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <cmath>

namespace Svg {

	struct Point {
		Point() {};
		Point(double x, double y) :x(x), y(y) {};
		double x = .0;
		double y = .0;
		friend std::ostream& operator <<(std::ostream& out, const Point& point) {
			return out << point.x << "," << point.y;
		}
	};

	struct Rgb {
		Rgb() {};
		Rgb(int r, int g, int b) : red(r), green(g), blue(b) {};
		int red = 0;
		int green = 0;
		int blue = 0;
		friend std::ostream& operator <<(std::ostream& out, const Rgb& rgb) {
			return out << "rgb(" << rgb.red << "," << rgb.green << "," << rgb.blue << ")";
		}
	};

	class Color {
	public:
		Color() {};
		Color(const char* color) : color(color) {};
		Color(const std::string& color) : color(color) {};
		Color(const Rgb& color) : color(color) {};
		friend std::ostream& operator <<(std::ostream& out, const Color& c) {
			if (c.color) {
				std::visit([&out](const auto& c) {out << c; }, c.color.value());
			}
			else out << "none";
			return out;
		}
	private:
		std::optional<std::variant<Rgb, std::string>> color;
	};

	const Color NoneColor = Color{};

	struct Vertexes {
		std::vector<Point> points;

		friend std::ostream& operator <<(std::ostream& out, const Vertexes& v) {
			for (const auto& point : v.points) {
				out << point << " ";
			}
			return out;
		}
	};

	template<typename T>
	struct Property {
		Property(const std::string& prop_name, const T& value) : prop_name(prop_name), value(value) {}
		friend std::ostream& operator <<(std::ostream& out, const Property& p) {
			return out << p.prop_name << "=\"" << p.value << "\" ";
		}
		const std::string& prop_name;
		const T& value;
	};



	template <typename ObjT>
	class Shape {
	public:
		Shape() {
			shape = static_cast<ObjT*>(this);
		}

		ObjT& SetFillColor(const Color& color) {
			fill = color;
			return *shape;
		}
		ObjT& SetStrokeColor(const Color& color) {
			stroke_color = color;
			return *shape;
		}
		ObjT& SetStrokeWidth(double width) {
			stroke_width = width;
			return *shape;
		}
		ObjT& SetStrokeLineCap(const std::string& type) {
			stroke_line_cap = type;
			return *shape;
		}
		ObjT& SetStrokeLineJoin(const std::string& type) {
			stroke_line_join = type;
			return *shape;
		}
		const ObjT* GetShape() const {
			return shape;
		}

		virtual void Render(std::ostream& out) const = 0;

		void RenderBasics(std::ostream& out) const {
			out << Property("fill", fill) << Property("stroke", stroke_color)
				<< Property("stroke-width", stroke_width);
			if (stroke_line_cap) out << Property("stroke-linecap", stroke_line_cap.value());
			if (stroke_line_join) out << Property("stroke-linejoin", stroke_line_join.value());
		}

		virtual ~Shape() = default;
	protected:
		ObjT* shape;
		Color fill;
		Color stroke_color;
		double stroke_width = 1.0;
		std::optional<std::string> stroke_line_cap;
		std::optional<std::string> stroke_line_join;
	};


	class Circle : public Shape<Circle> {
	public:
		Circle() {}
		Circle& SetCenter(Point p) {
			cx = p.x;
			cy = p.y;
			return *this;
		}
		Circle& SetRadius(double radius) {
			r = radius;
			return *this;
		}
		void Render(std::ostream& out) const {
			out << "<circle ";
			RenderBasics(out);
			out << Property("cx", cx) << Property("cy", cy) << Property("r", r);
			out << "/> ";
		}
	private:
		double cx = .0;
		double cy = .0;
		double r = 1.;
	};


	class Polyline : public Shape<Polyline> {
	public:
		Polyline() {}
		Polyline& AddPoint(Point p) {
			points.points.push_back(p);
			return *this;
		}
		void Render(std::ostream& out) const {
			out << "<polyline ";
			RenderBasics(out);
			out << Property("points", points);
			out << "/> ";
		}
	private:
		Vertexes points;
	};


	class Text : public Shape<Text> {
	public:
		Text() {}
		Text& SetPoint(Point p) {
			x = p.x;
			y = p.y;
			return *this;
		}
		Text& SetOffset(Point p) {
			dx = p.x;
			dy = p.y;
			return *this;
		}
		Text& SetFontSize(uint32_t size) {
			font_size = size;
			return *this;
		}
		Text& SetFontFamily(const std::string& family) {
			font_family = family;
			return *this;
		}
		Text& SetData(const std::string& data) {
			text = data;
			return *this;
		}
		void Render(std::ostream& out) const {
			out << "<text ";
			RenderBasics(out);
			out << Property("x", x) << Property("y", y)
				<< Property("dx", dx) << Property("dy", dy) << Property("font-size", font_size);
			if (font_family) out << Property("font-family", font_family.value());
			out << ">" << text << "</text> ";
		}
	private:
		std::string text;
		double x = .0;
		double y = .0;
		double dx = .0;
		double dy = .0;
		uint32_t font_size = 1;
		std::optional<std::string> font_family;
	};



	class Document {
	public:
		using AnyShape = std::variant<const Circle, const Polyline, const Text>;

		Document() {};

		template<typename ObjT>
		void Add(const Shape<ObjT>& shape) {
			shapes.push_back(*shape.GetShape());
		}

		void Render(std::ostream& out) {
			out << header_tag << svg_open_tag;
			RenderObjects(out);
			out << svg_close_tag;
		}
	private:
		const std::string header_tag = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";
		const std::string svg_open_tag = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">";
		const std::string svg_close_tag = "</svg>";
	private:
		std::vector<AnyShape> shapes;

		void RenderObjects(std::ostream& out) {
			for (auto object : shapes) {
				std::visit(
					[&out](const auto& obj) {obj.Render(out); },
					object);
			}
		}
	};
}


int main() {
	std::ofstream out("svg.svg");
	Svg::Document svg;

	svg.Add(
		Svg::Polyline{}
		.SetStrokeColor(Svg::Rgb{ 140, 198, 63 })  // soft green
		.SetStrokeWidth(16)
		.SetStrokeLineCap("round")
		.AddPoint({ 50, 50 })
		.AddPoint({ 250, 250 })
	);

	for (const auto point : { Svg::Point{50, 50}, Svg::Point{250, 250} }) {
		svg.Add(
			Svg::Circle{}
			.SetFillColor("white")
			.SetRadius(6)
			.SetCenter(point)
		);
	}

	svg.Add(
		Svg::Text{}
		.SetPoint({ 50, 50 })
		.SetOffset({ 10, -10 })
		.SetFontSize(20)
		.SetFontFamily("Verdana")
		.SetFillColor("black")
		.SetData("C")
	);
	svg.Add(
		Svg::Text{}
		.SetPoint({ 250, 250 })
		.SetOffset({ 10, -10 })
		.SetFontSize(20)
		.SetFontFamily("Verdana")
		.SetFillColor("black")
		.SetData("C++")
	);

	svg.Render(out);
}
