#include <cstddef>
#include <array>
#include <cstdint>
#include <algorithm>


struct Nucleotide {
  char Symbol;
  size_t Position;
  int ChromosomeNum;
  int GeneNum;
  bool IsMarked;
  char ServiceInfo;
};

const std::array<char, 4> NUCLS = { 'A', 'T', 'G', 'C' };

struct CompactNucleotide {
  uint32_t position;
  uint32_t symbol : 2;
  uint32_t chromosome_num : 6;
  uint32_t gene_num : 15;
  uint32_t is_marked : 1;
  uint32_t service_info : 8;
};


bool operator == (const Nucleotide& lhs, const Nucleotide& rhs) {
  return (lhs.Symbol == rhs.Symbol)
      && (lhs.Position == rhs.Position)
      && (lhs.ChromosomeNum == rhs.ChromosomeNum)
      && (lhs.GeneNum == rhs.GeneNum)
      && (lhs.IsMarked == rhs.IsMarked)
      && (lhs.ServiceInfo == rhs.ServiceInfo);
}


CompactNucleotide Compress(const Nucleotide& n) {
  size_t symb = std::distance(
    NUCLS.begin(), std::find(NUCLS.begin(), NUCLS.end(), n.Symbol)
  );
  return {
    static_cast<uint32_t>(n.Position),
    static_cast<uint32_t>(symb),
    static_cast<uint32_t>(n.ChromosomeNum),
    static_cast<uint32_t>(n.GeneNum),
    static_cast<uint32_t>(n.IsMarked),
    static_cast<uint32_t>(n.ServiceInfo)
  };
};


Nucleotide Decompress(const CompactNucleotide& cn) {
  return {
    NUCLS[cn.symbol],
    cn.position,
    static_cast<int>(cn.chromosome_num),
    static_cast<int>(cn.gene_num),
    static_cast<bool>(cn.is_marked),
    static_cast<char>(cn.service_info)
  };
}
