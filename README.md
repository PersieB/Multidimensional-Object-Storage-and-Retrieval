# Multidimensional-Object-Storage-and-Retrieval

In recent times, Spatial data has attracted enough attention that it is being used almost everywhere right from building simple applications such as booking a taxi ride to complex
applications such as autonomous driving. While spatial databases have rapidly proliferated in the past decade, extensive research has been conducted on the use of data structures to design efficient
algorithms to optimize the storing, retrieving and displaying of spatial data. Research has led to the development of multidimensional index structures such
as R-tree and Kd-tree among others. Research shows that the GIST framework adopted by Database Management Systems performs slower than the custom implementation
of the multidimensional index structures on which the framework was built. As a bold step in relying on a custom implementation of the multidimensional index
structures, this thesis considered the problem of handling spatial data in geographic coordinates form (i.e latitudes and longitudes) in a custom implementation
of two index structures: R-tree and Kd-tree, as these structures cannot handle effectively geographic coordinates by design. The thesis used coordinate
transformation to convert the geographic coordinates into cartesian form for effective handling by both structures mentioned above. Experiments were also
conducted to measure the performances of the proposed algorithm that merges coordinate transformation and the custom implementation of R-tree and Kd-tree
in terms of object storage, retrieval and removal time costs.
