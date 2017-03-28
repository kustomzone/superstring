#include <string>
#include <vector>
#include "patch.h"
#include "point.h"
#include "range.h"
#include "text.h"

class TextBuffer {
  struct Layer;
  Text base_text;
  Layer *top_layer;

  TextBuffer(Text &&base_text);

public:
  TextBuffer();
  TextBuffer(std::u16string text);
  ~TextBuffer();

  bool reset(Text &&);
  bool save(std::ostream &stream, const char *encoding_name, size_t chunk_size);

  uint32_t size() const;
  Point extent() const;
  uint32_t line_length_for_row(uint32_t row);
  Point clip_position(Point);
  Range clip_range(Range);
  Text text();
  Text text_in_range(Range range);
  void set_text(Text &&new_text);
  void set_text_in_range(Range old_range, Text &&new_text);

  std::string get_dot_graph() const;

  class Snapshot {
    friend class TextBuffer;
    TextBuffer &buffer;
    Layer &layer;

    Snapshot(TextBuffer &, Layer &);

  public:
    ~Snapshot();
    uint32_t size() const;
    Point extent() const;
    uint32_t line_length_for_row(uint32_t) const;
    std::vector<TextSlice> chunks() const;
    std::vector<TextSlice> chunks_in_range(Range) const;
    Text text() const;
    Text text_in_range(Range) const;
  };

  friend class Snapshot;
  const Snapshot *create_snapshot();
};
