---Overview

This repository implements a CPU ray tracer inspired by physically-based rendering principles. It computes lighting by simulating rays of light bouncing through the scene, evaluating surface materials, and accumulating color contributions over many samples.

The renderer includes:

Lambertian diffuse reflection

Metal with adjustable fuzziness

Dielectric / glass using Snell’s Law + Fresnel

Depth of field, anti-aliasing, and multi-bounce paths

Support for primitives (spheres, planes) and optional model loading

---Features
--Material System

Lambertian (Diffuse)
True diffuse scattering in random hemisphere directions.

Metal
Reflective surfaces with optional fuzziness.

Dielectric (Glass)
Supports refraction using:

Snell's law

Schlick’s approximation for Fresnel reflectance

Total internal reflection

--Rendering Capabilities

Recursive ray evaluation with customizable max depth

Anti-aliasing by multiple samples per pixel

Random scene generation (if supported)

Depth of field using thin-lens camera simulation

Multi-threading (if implemented in your repo)

Outputs .ppm or .png (depending on code)

--Geometry Support

Spheres

Planes


---Installation
Requirements

Visual Studio 2022 (or 2019)

C++17 or later

glm (optional, if your code uses it somewhere)

No external graphics library required — this is a CPU-only renderer

If needed through vcpkg:

vcpkg install glm



---Running the Project (Visual Studio Only)

These instructions assume you run everything inside Visual Studio, just like your OpenGL project.

1. Open the Project

Launch Visual Studio.

Go to File → Open → Folder…

Select the root folder of the repo (RayTracerRepo/).

2. Select Build Configuration

Top toolbar:

Configuration: Debug or Release

Platform: x64

Rendering is slow in Debug — for final images, choose Release.

3. Build the Project

Press Ctrl + Shift + B

OR choose Build → Build Solution

OR click the hammer icon

Your executable will compile and appear in the x64/Debug or x64/Release folder.

4. Run the Ray Tracer

Press F5 (Run with Debugging),

OR press Ctrl + F5 (Run without Debugging),

OR click the green play arrow in the toolbar.

A console window will appear and begin printing render progress.


---Technical Details
--Ray Generation

The ray tracer casts a primary ray for each pixel:

Ray r = camera.getRay(u, v);
color += TraceRay(r, depth);

--Shading Model

Materials expose:

bool scatter(const Ray& in, const Hit& hit, vec3& attenuation, Ray& scattered);

Lambertian

Random hemisphere scattering:

scatterDir = normal + randomUnitVector();
attenuation = albedo;

Metal

Reflective with optional fuzz:

reflected = reflect(unitDir, normal);
scattered = Ray(hitPos, reflected + fuzz * randomInUnitSphere());

Dielectric (Glass)

Snell's Law

Total internal reflection

Fresnel reflectance (Schlick’s approximation)

This material produces realistic refraction and reflection mixing:

float cosTheta = dot(-unitDir, normal);
float reflectProb = schlick(cosTheta, refIdx);

--Anti-Aliasing

Each pixel traces N random samples, jittered within the pixel:

for (int s = 0; s < samples; s++)
    color += TraceRay(camera.getRay(u + rand01(), v + rand01()), depth);


Final color is averaged.

--Multiple Bounce Light Transport

Rays recursively bounce until:

Max depth reached

Material absorbs the ray

This allows indirect lighting and caustics.


---Screenshots of differnt stages of development


<img width="806" height="647" alt="Screenshot 2025-12-03 144205" src="https://github.com/user-attachments/assets/b6bd0071-1c25-4ce0-b126-131f2f7eb997" />
<img width="802" height="647" alt="Screenshot 2025-12-04 093828" src="https://github.com/user-attachments/assets/526b6247-3cf7-4064-8508-f54417cdbcde" />
<img width="795" height="642" alt="Screenshot 2025-12-04 093943" src="https://github.com/user-attachments/assets/948bc24e-e2e3-46de-906e-cb2e96fce133" />

<img width="805" height="641" alt="Screenshot 2025-12-05 093759" src="https://github.com/user-attachments/assets/81064fd9-829f-496e-9601-5b895e98b319" />
<img width="805" height="644" alt="Screenshot 2025-12-05 094211" src="https://github.com/user-attachments/assets/8f8dc235-906f-49ed-85e9-52cfcb0175fa" />

<img width="795" height="644" alt="Screenshot 2025-12-08 102724" src="https://github.com/user-attachments/assets/0fc696ec-0459-459d-b9d0-9baf546bc78b" />
<img width="798" height="641" alt="Screenshot 2025-12-08 103449" src="https://github.com/user-attachments/assets/a0922960-34e8-4932-b9be-e04a447bba7a" />

<img width="800" height="639" alt="Screenshot 2025-12-09 102725" src="https://github.com/user-attachments/assets/39ecd3ed-c774-4eda-824a-220aaca044cd" />
<img width="793" height="639" alt="Screenshot 2025-12-09 103623" src="https://github.com/user-attachments/assets/1e285c79-3f7a-4cd7-9d66-b727785890f0" />


Attribution

This project references or includes concepts/assets from:

"Ray Tracing in One Weekend" by Peter Shirley (inspiration).
