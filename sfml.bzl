def sfml_repository():
    # sfml_path = select({
    #     "@bazel_tools//src/conditions:darwin": "/opt/homebrew/Cellar/sfml/2.5.1_2",  # M1 Mac <-- Replace this with your SFML path
    #     "@bazel_tools//src/conditions:linux_x86_64": "/usr/local/Cellar/sfml/2.5.1_2",  # M1 Mac <-- Replace this with your SFML path
    #     "@bazel_tools//src/conditions:windows": "C:/Program Files (x86)/SFML-2.5.1",  # Windows <-- Replace this with your SFML path
    # })
    sfml_path = "/opt/homebrew/Cellar/sfml/2.5.1_2"  # M1 Mac <-- Replace this with your SFML path

    native.new_local_repository(
        name = "sfml",
        build_file = "third_party/SFML/BUILD.bazel",
        path = sfml_path,
    )

# TODO: maybe go fully from source inside sandbox instead of using the precompiled binaries
# (would be more portable, but also significantly more complicated)
# def _sfml_repository_impl(ctx):
#     ctx.report_progress("Downloading SFML")
#     ctx.download(
#         ctx.attr.urls,
#         sha256 = ctx.attr.sha256,
#         output = "go.tar.gz",
#     )
