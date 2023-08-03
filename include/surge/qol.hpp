#pragma once

namespace ImGui {
	void PushFont(const surge::Font &font);
}

namespace ImPlot {
	// IMPLOT_TMP void PlotLine(const char* label_id, const T* values, int count, double xscale=1,
	// double xstart=0, ImPlotLineFlags flags=0, int offset=0, int stride=sizeof(T));
	//
	// IMPLOT_TMP
	// void PlotLine(const char* label_id, const T* xs, const T* ys, int count, ImPlotLineFlags
	// flags=0, int offset=0, int stride=sizeof(T));

	template<typename Data, typename Int = uint64_t, typename Float = double>
	void PlotLine(const std::string &labelID, const std::initializer_list<Data> &data,
				  Float xScale = 1.0, Float xStart = 0.0, ImPlotLineFlags flags = 0, Int offset = 0,
				  Int stride = static_cast<Int>(sizeof(Data))) {
		PlotLine(labelID, std::vector<Data>(data), xScale, xStart, flags, offset, stride);
	}

	template<typename Data, typename Int = uint64_t, typename Float = double>
	void PlotLine(const std::string &labelID, const std::vector<Data> &data, Float xScale = 1.0,
				  Float xStart = 0.0, ImPlotLineFlags flags = 0, Int offset = 0,
				  Int stride = static_cast<Int>(sizeof(Data))) {
		PlotLine(labelID.c_str(),
				 data.data(),
				 static_cast<int>(data.size()),
				 static_cast<double>(xScale),
				 static_cast<double>(xStart),
				 flags,
				 static_cast<int>(offset),
				 static_cast<int>(stride));
	}

	template<typename ShapeType, typename StorageType, typename Int = uint64_t,
			 typename Float	 = double,
			 typename Scalar = typename librapid::typetraits::TypeInfo<StorageType>::Scalar>
	void PlotLine(const std::string &labelID,
				  const librapid::array::ArrayContainer<ShapeType, StorageType> &data,
				  Float xScale = 1.0, Float xStart = 0.0, ImPlotLineFlags flags = 0, Int offset = 0,
				  Int stride = static_cast<Int>(sizeof(Scalar))) {
		LIBRAPID_ASSERT(data.ndim() == 1, "PlotLine only supports 1D arrays");
		auto storage = data.storage().toHostStorageUnsafe();
		auto ptr	 = storage.begin();

		PlotLine(labelID.c_str(),
				 ptr,
				 static_cast<int>(data.shape().size()),
				 static_cast<double>(xScale),
				 static_cast<double>(xStart),
				 flags,
				 static_cast<int>(offset),
				 static_cast<int>(stride));
	}

	template<typename Data, typename Int = uint64_t, typename Float = double>
	void PlotLine(const std::string &labelID, const std::initializer_list<Data> &xData,
				  const std::initializer_list<Data> &yData, ImPlotLineFlags flags = 0,
				  Int offset = 0, Int stride = static_cast<Int>(sizeof(Data))) {
		PlotLine(
		  labelID, std::vector<Data>(xData), std::vector<Data>(yData), flags, offset, stride);
	}

	template<typename Data, typename Int = uint64_t, typename Float = double>
	void PlotLine(const std::string &labelID, const std::vector<Data> &xData,
				  const std::vector<Data> &yData, ImPlotLineFlags flags = 0, Int offset = 0,
				  Int stride = static_cast<Int>(sizeof(Data))) {
		LIBRAPID_ASSERT(xData.size() == yData.size(), "xData and yData must be the same size");
		PlotLine(labelID.c_str(),
				 xData.data(),
				 yData.data(),
				 static_cast<int>(xData.size()),
				 flags,
				 static_cast<int>(offset),
				 static_cast<int>(stride));
	}

	template<typename ShapeType, typename StorageType, typename Int = uint64_t,
			 typename Float	 = double,
			 typename Scalar = typename librapid::typetraits::TypeInfo<StorageType>::Scalar>
	void PlotLine(const std::string &labelID,
				  const librapid::array::ArrayContainer<ShapeType, StorageType> &xData,
				  const librapid::array::ArrayContainer<ShapeType, StorageType> &yData,
				  ImPlotLineFlags flags = 0, Int offset = 0,
				  Int stride = static_cast<Int>(sizeof(Scalar))) {
		LIBRAPID_ASSERT(xData.ndim() == 1, "PlotLine only supports 1D arrays");
		LIBRAPID_ASSERT(yData.ndim() == 1, "PlotLine only supports 1D arrays");

		auto xStorage = xData.storage().toHostStorageUnsafe();
		auto yStorage = yData.storage().toHostStorageUnsafe();
		auto xPtr	  = xStorage.begin();
		auto yPtr	  = yStorage.begin();

		LIBRAPID_ASSERT(xData.shape().size() == yData.shape().size(),
						"xData and yData must be the same size");

		PlotLine(labelID.c_str(),
				 xPtr,
				 yPtr,
				 static_cast<int>(xData.shape().size()),
				 flags,
				 static_cast<int>(offset),
				 static_cast<int>(stride));
	}
} // namespace ImPlot
